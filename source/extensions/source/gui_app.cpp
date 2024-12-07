#include <extensions/defs/gui_def.hpp>

#if defined(OMNI_GUI_EXTENSION_APP)
    // TODO: need to add the following for OMNI_OS_APPLE ->
    /*
        int main(int argc, char* argv[])
        {
            // create the autorelease pool
            NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
            // create the application object 
            NSApp = [NSApplication sharedApplication];

            // set up the window and drawing mechanism
            setup();

            // run the main event loop
            [NSApp run];
            // we get here when the window is closed
            [NSApp release];      // release the app 
            [pool release];       // release the pool

            return 0;
        }
    */
    // TODO: need to add the following for OMNI_OS_WIN ->
    /*
        INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
        {
            // Run the message loop.

            MSG msg = { };
            while (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            return 0;
        }
    */
    // TODO: need to add the following for OMNI _OS_*/_GUI_USE_X
    /*
        int main(int argc, char* argv[])
        {
            // Open a display.
            Display* d = ::XOpenDisplay(0);

            if (d) {
                // Create the window
                Window w = XCreateWindow(d, DefaultRootWindow(d), 0, 0, 200,
                100, 0, CopyFromParent, CopyFromParent,
                CopyFromParent, 0, 0);

                // Show the window
                XMapWindow(d, w);
                XFlush(d);

                // Sleep long enough to see the window.
                sleep(3);

                XDestroyWindow(d, w);
            }

            return 0;
        }
    */
    int run_gui(bool kill_worker_on_signal)
    {
        OMNI_D2_FW("GUI application start");
        OMNI_SAFE_APP_LOCK_FW
        omni::application::m_isrun = true;
        if (omni::application::start_()) {
            OMNI_SAFE_APP_UNLOCK_FW
            OMNI_THREAD_TRY_FW
            omni::application::start_()();
            OMNI_THREAD_CATCH_FW
            OMNI_SAFE_APP_LOCK_FW
        }
        omni::application::base_thread::instance().start();
        OMNI_D2_FW("entering base GUI application loop...");
        do {
            OMNI_SAFE_APP_UNLOCK_FW
            omni::application::wait_().wait();
            OMNI_SAFE_APP_LOCK_FW
            // if user set cancel signal request, loop until they unset it
            if (omni::application::m_igsig) {
                omni::application::wait_().reset();
                /* std::signal specifies that the signal handlers can be reset back to the default handler
                so we must re-install the signal handlers to be able to continue to catch; note that we
                do not need to re-install the WinAPI omni_application_base_win_ctrl_handler. */
                omni::application::base::set_signal_handlers();
            }
        } while (omni::application::m_igsig);
        OMNI_SAFE_APP_UNLOCK_FW
        omni::application::base_thread::instance().wait(kill_worker_on_signal);
        OMNI_SAFE_APP_LOCK_FW
        if (omni::application::shut_()) {
            OMNI_SAFE_APP_UNLOCK_FW
            OMNI_THREAD_TRY_FW
            omni::application::shut_()();
            OMNI_THREAD_CATCH_FW
            OMNI_SAFE_APP_LOCK_FW
        }
        int ret = omni::application::m_ret;
        omni::application::m_isrun = false;
        OMNI_SAFE_APP_UNLOCK_FW
        OMNI_DV2_FW("base application thread complete, returning ", ret);
        return ret;
    }
#endif