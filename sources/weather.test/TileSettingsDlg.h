#pragma once

#include <weather/CurrentWeatherTile.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/weakref.h>

class TileSettingsDlg : public wxDialog
{
public:
	TileSettingsDlg( wxWindow* parent, weather::CurrentWeatherTile::Settings& settings );
	virtual ~TileSettingsDlg() = default;

private:
    void CreateMenuBar();

    weather::CurrentWeatherTile::Settings& m_Settings;

    wxWeakRef<wxCheckBox> m_ShowCompact;
    wxWeakRef<wxCheckBox> m_ShowFeelsLike;
    wxWeakRef<wxCheckBox> m_ShowHighLow;
    wxWeakRef<wxCheckBox> m_UseCelsius;
};
