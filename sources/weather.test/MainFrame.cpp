#include "MainFrame.h"
#include "TileSettingsDlg.h"

#include <wx/clipbrd.h>
#include <wx/textfile.h>

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxString apiKey = GetApiKey();

    if( apiKey.IsEmpty() )
    {
        wxMessageBox("API key not found. Please create a file named 'api-key.txt' in the project root directory with your weatherapi.com API key.", "Error", wxOK | wxICON_ERROR);
        Close(true);
        return;
    }

    m_WeatherAPI = std::make_unique<weather::WeatherAPI>(apiKey.ToStdString());

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    m_CurrentWeatherTile = new weather::CurrentWeatherTile(this, "Halifax", *m_WeatherAPI, m_TileSettings);
    sizer->Add(m_CurrentWeatherTile, 0, wxALL, 10);

    CreateMenuBar();

    SetStatusBar(new wxStatusBar(this, wxID_ANY));
    SetStatusText("Welcome to the weather.test application!");
}

void MainFrame::CreateMenuBar()
{
    // Create a menu bar
    auto* menuBar = new wxMenuBar();

    // File menu
    auto* fileMenu = new wxMenu();
    fileMenu->Append(wxID_EXIT, "&Exit\tAlt-X", "Quit this program");
    menuBar->Append(fileMenu, "&File");

    // Settings menu
    auto* settingsMenu = new wxMenu();
    auto locationItem = settingsMenu->Append(wxID_ANY, "&Location");
    auto tileSettingsItem = settingsMenu->Append(wxID_ANY, "&Tile Settings" );

    menuBar->Append(settingsMenu, "&Settings");

    // Help menu
    auto* helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    menuBar->Append(helpMenu, "&Help");

    // Attach the menu bar to the frame
    SetMenuBar(menuBar);

    // Bind menu events
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) { Close(true); }, wxID_EXIT);

    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        wxMessageBox("Sample app for weather lib.", "About weather.test", wxOK | wxICON_INFORMATION);
        }, wxID_ABOUT);

    Bind(wxEVT_MENU, [this](wxCommandEvent& event) { DoLocation(); }, locationItem->GetId() );
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) { DoTileSettings(); }, tileSettingsItem->GetId() );
}

void MainFrame::DoTileSettings()
{
    TileSettingsDlg dlg(this, m_TileSettings);

    if (dlg.ShowModal() == wxID_OK)
    {
        m_CurrentWeatherTile->SetSettings(m_TileSettings);
    }

}

void MainFrame::DoLocation()
{
    wxString location = wxGetTextFromUser("Enter a location:", "Location", m_CurrentWeatherTile->GetLocation());
    if (!location.IsEmpty())
    {
         m_CurrentWeatherTile->SetLocation(location);
    }
}

wxString MainFrame::GetApiKey() const
{
    wxTextFile apiKeyFile(wxT("../../api-key.txt"));
    if (apiKeyFile.Exists() && apiKeyFile.Open())
    {
        wxString apiKey = apiKeyFile.GetFirstLine();
        apiKeyFile.Close();
        return apiKey;
    }
    return wxEmptyString;
}