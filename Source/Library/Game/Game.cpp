#include "Game/Game.h"

namespace library
{
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Game::Game

      Summary:  Constructor

      Args:     PCWSTR pszGameName
                  Name of the game

      Modifies: [m_pszGameName, m_mainWindow, m_renderer].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Game::Game definition (remove the comment)
    --------------------------------------------------------------------*/
    Game::Game(_In_ PCWSTR pszGameName) : m_pszGameName(pszGameName)
    {
        m_mainWindow = std::make_unique<MainWindow>();
        m_renderer = std::make_unique<Renderer>();
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Game::Initialize

      Summary:  Initializes the components of the game

      Args:     HINSTANCE hInstance
                  Handle to the instance
                INT nCmdShow
                  Is a flag that says whether the main application window
                  will be minimized, maximized, or shown normally

      Modifies: [m_mainWindow, m_renderer].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Game::Initializes definition (remove the comment)
    --------------------------------------------------------------------*/
    HRESULT Game::Initialize(_In_ HINSTANCE hInstance, _In_ INT nCmdShow)
    {
        if (FAILED(m_mainWindow->Initialize(hInstance, nCmdShow, m_pszGameName)))
        {
            return E_FAIL;
        }
        if (FAILED(m_renderer->Initialize(m_mainWindow->GetWindow())))
        {
            return E_FAIL;
        }
        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Game::Run

      Summary:  Runs the game loop

      Returns:  INT
                  Status code to return to the operating system
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Game::Run definition (remove the comment)
    --------------------------------------------------------------------*/
    INT Game::Run()
    {
        LARGE_INTEGER StartingTime, EndingTime;
        float ElapsedSeconds = 0.0f;
        LARGE_INTEGER Frequency;

        MSG msg = { 0 };
        QueryPerformanceFrequency(&Frequency);
        QueryPerformanceCounter(&StartingTime);
        while (WM_QUIT != msg.message)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                QueryPerformanceCounter(&EndingTime);
                ElapsedSeconds = (FLOAT)(EndingTime.QuadPart - StartingTime.QuadPart) / (FLOAT)Frequency.QuadPart;
                QueryPerformanceCounter(&StartingTime);
                m_renderer->HandleInput(m_mainWindow->GetDirections(), m_mainWindow->GetMouseRelativeMovement(), ElapsedSeconds);
                m_renderer->Update(ElapsedSeconds);
                m_renderer->Render();  // Do some rendering
                m_mainWindow->ResetMouseMovement();
            }
        }
        return static_cast<INT>(msg.wParam);
    }
    
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Game::GetGameName

      Summary:  Returns the name of the game

      Returns:  PCWSTR
                  Name of the game
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Game::GetGameName definition (remove the comment)
    --------------------------------------------------------------------*/
    PCWSTR Game::GetGameName() const
    {
        return m_pszGameName;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Game::GetWindow

      Summary:  Returns the main window

      Returns:  std::unique_ptr<MainWindow>&
                  The main window
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Game::GetWindow definition (remove the comment)
    --------------------------------------------------------------------*/
    std::unique_ptr<MainWindow>& Game::GetWindow()
    {
        return m_mainWindow;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Game::GetRenderer

      Summary:  Returns the renderer

      Returns:  std::unique_ptr<Renderer>&
                  The renderer
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Game::GetRenderer definition (remove the comment)
    --------------------------------------------------------------------*/
    std::unique_ptr<Renderer>& Game::GetRenderer()
    {
        return m_renderer;
    }

}
