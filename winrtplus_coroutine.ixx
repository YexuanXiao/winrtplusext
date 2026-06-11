export module winrtplus_coroutine;

import winrt_base;
import std;

namespace winrtplus::impl
{
struct dispatched_handler_state
{
    std::coroutine_handle<> handle{};
    bool orphaned{};
};

struct dispatcher_handler
{
    dispatched_handler_state *m_state{};

    dispatcher_handler(dispatched_handler_state *s) : m_state(s)
    {
    }
    dispatcher_handler(dispatcher_handler &&o) noexcept : m_state(std::exchange(o.m_state, {}))
    {
    }

    ~dispatcher_handler()
    {
        if (m_state && m_state->handle)
        {
            m_state->orphaned = true;
            Complete();
        }
    }

    void operator()()
    {
        Complete();
    }

    void Complete()
    {
        auto state = std::exchange(m_state, nullptr);
        std::exchange(state->handle, {}).resume();
    }
};

struct dispatcher_state_guard
{
    dispatched_handler_state *m_state{};

    ~dispatcher_state_guard()
    {
        if (m_state)
        {
            m_state->handle = nullptr;
        }
    }
};
} // namespace winrtplus::impl

export namespace winrtplus
{
template <typename Dispatcher>
struct dispatcher_traits;

// Resumes coroutine execution on the thread associated with the dispatcher, or throws
// an exception (from an arbitrary thread) if unable.
template <typename Dispatcher, typename Traits = dispatcher_traits<Dispatcher>,
          typename = std::void_t<decltype(sizeof(Traits))>>
[[nodiscard]] auto resume_foreground(Dispatcher const &dispatcher,
                                     typename Traits::Priority priority = Traits::Priority::Normal)
{
    using Priority = typename Traits::Priority;
    using Handler = typename Traits::Handler;
    using Scheduler = typename Traits::Scheduler;

    struct awaitable
    {
      private:
        Dispatcher const &m_dispatcher;
        Priority const m_priority;
        impl::dispatched_handler_state m_state;

      public:
        awaitable(Dispatcher const &d, Priority p) noexcept : m_dispatcher(d), m_priority(p)
        {
        }

        bool await_ready() const noexcept
        {
            return false;
        }

        void await_suspend(std::coroutine_handle<> handle)
        {
            m_state.handle = handle;
            Handler handler{impl::dispatcher_handler(&m_state)};
            impl::dispatcher_state_guard guard{&m_state};
            // The return value of RunAsync/TryEnqueue is not reliable. Use the dispatcher_handler destructor
            // to detect whether the work item failed to run.
            Scheduler{}(m_dispatcher, m_priority, handler);
            guard.m_state = nullptr;
        }

        void await_resume() const
        {
            if (m_state.orphaned)
            {
                // If task enqueue fails (for example, because the queue is closed), an exception is thrown.
                // If the exception is not caught, the coroutine will be destroyed, preventing it from
                // running on the wrong thread or leaks.
                throw winrt::hresult_error(static_cast<winrt::hresult>(0x800701AB));
            }
        }
    };

    return awaitable{dispatcher, priority};
}

template <typename Dispatcher, typename Traits = dispatcher_traits<Dispatcher>,
          typename = std::void_t<decltype(sizeof(Traits))>>
inline auto operator co_await(Dispatcher const &dispatcher)
{
    return resume_foreground(dispatcher);
}
} // namespace winrtplus

#if __has_include("winrt/Windows.System.h")
import winrt.Windows.System;
namespace winrtplus
{
template <>
struct dispatcher_traits<winrt::Windows::System::DispatcherQueue>
{
    using Priority = winrt::Windows::System::DispatcherQueuePriority;
    using Handler = winrt::Windows::System::DispatcherQueueHandler;
    using Scheduler = decltype([](auto const &d, auto const &p, auto const &h) { d.TryEnqueue(p, h); });
};
} // namespace winrtplus
#endif

#if __has_include("winrt/Microsoft.UI.Dispatching.h")
import winrt.Microsoft.UI.Dispatching;
namespace winrtplus
{
template <>
struct dispatcher_traits<winrt::Microsoft::UI::Dispatching::DispatcherQueue>
{
    using Priority = winrt::Microsoft::UI::Dispatching::DispatcherQueuePriority;
    using Handler = winrt::Microsoft::UI::Dispatching::DispatcherQueueHandler;
    using Scheduler = decltype([](auto const &d, auto const &p, auto const &h) { d.TryEnqueue(p, h); });
};
} // namespace winrtplus
#endif

#if __has_include("winrt/Windows.UI.Core.h")
import winrt.Windows.UI.Core;
namespace winrtplus
{
template <>
struct dispatcher_traits<winrt::Windows::UI::Core::CoreDispatcher>
{
    using Priority = winrt::Windows::UI::Core::CoreDispatcherPriority;
    using Handler = winrt::Windows::UI::Core::DispatchedHandler;
    using Scheduler = decltype([](auto const &d, auto const &p, auto const &h) { d.RunAsync(p, h); });
};
} // namespace winrtplus
#endif
