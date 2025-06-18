#pragma once

#include <weather/WeatherAPI.h>
#include <weather/CurrentWeatherTile.h>

#include <wx/wx.h>

#include <memory>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MainFrame() = default;

private:
    void CreateMenuBar();
    void DoTileSettings();
    void DoLocation();
    wxString GetApiKey() const;

    std::unique_ptr<weather::WeatherAPI> m_WeatherAPI;
    weather::CurrentWeatherTile::Settings m_TileSettings;
    wxWeakRef<weather::CurrentWeatherTile> m_CurrentWeatherTile;
};