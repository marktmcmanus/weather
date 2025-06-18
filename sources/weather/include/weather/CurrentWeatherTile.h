#pragma once

#include "weather/WeatherAPI.h"

#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
#include <wx/weakref.h>
#include <wx/sizer.h>

namespace weather
{
	class CurrentWeatherTile : public wxPanel
	{
	public:
		enum class TileStyle
		{
			Normal = 0,
            Compact = 1
		};

		struct Settings
		{
			TileStyle style = TileStyle::Normal;
            bool includeFeelsLike = true;
            bool includeHighLow = false;
            bool celsius = true;
        };

		CurrentWeatherTile(wxWindow* parent, wxString location, WeatherAPI& weatherAPI, const Settings& settings = {});
		virtual ~CurrentWeatherTile();

        void SetSettings(const Settings& settings);

        wxString GetLocation() const { return m_Location; }
        void SetLocation(const wxString& location);

        void UpdateWeatherInfo();

	private:
		void CreateNormalLayout();
        void CreateCompactLayout();

		wxString m_Location;
        Settings m_Settings;
		WeatherAPI& m_WeatherAPI;

        wxBoxSizer* m_MainSizer;
		wxWeakRef<wxStaticText> m_TemperatureLabel;
		wxWeakRef<wxStaticText> m_ConditionLabel;
		wxWeakRef<wxStaticText> m_FeelsLikeLabel;
		wxWeakRef<wxStaticText> m_HiLowLabel;
        wxWeakRef<wxStaticBitmap> m_WeatherIcon;

	};
}