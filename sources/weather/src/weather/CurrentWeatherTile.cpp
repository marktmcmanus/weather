#include "weather/CurrentWeatherTile.h"

#include <wx/wx.h>

weather::CurrentWeatherTile::CurrentWeatherTile(wxWindow* parent, wxString location, WeatherAPI& weatherAPI, const Settings& settings) :
    wxPanel(parent, wxID_ANY),
    m_Location(location),
    m_WeatherAPI(weatherAPI),
    m_Settings(settings)
{
    m_MainSizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(m_MainSizer);

    if (m_Settings.style == weather::CurrentWeatherTile::TileStyle::Compact)
    {
        CreateCompactLayout();
    }
    else
    {
        CreateNormalLayout();
    }

    UpdateWeatherInfo();
}

weather::CurrentWeatherTile::~CurrentWeatherTile()
{

}

void weather::CurrentWeatherTile::SetSettings(const Settings& settings)
{
    m_Settings = settings;
    m_MainSizer->Clear(true);
    if (m_Settings.style == weather::CurrentWeatherTile::TileStyle::Compact)
    {
        CreateCompactLayout();
    }
    else
    {
        CreateNormalLayout();
    }
    Layout();
    UpdateWeatherInfo();
}

void weather::CurrentWeatherTile::SetLocation(const wxString& location)
{
    m_Location = location;
    UpdateWeatherInfo();
}

void weather::CurrentWeatherTile::UpdateWeatherInfo()
{
    m_WeatherAPI.GetForecast(m_Location.ToStdString(), 1, [this](const weather::Forecast& forecast, const weather::Current& curr, const weather::Location& location) {

        if (m_TemperatureLabel != nullptr)
        {
            wxString str = wxString::Format("%d°", static_cast<int>(m_Settings.celsius ? curr.temp_c : curr.temp_f));
            m_TemperatureLabel->SetLabel(str);
        }

        if (m_ConditionLabel != nullptr)
        {
            m_ConditionLabel->SetLabel(curr.condition.text);
        }

        if (m_Settings.includeFeelsLike && m_FeelsLikeLabel != nullptr)
        {
            wxString feelsLikeStr = wxString::Format("Feels like %d", static_cast<int>(m_Settings.celsius ? curr.feelslike_c : curr.feelslike_f));
            m_FeelsLikeLabel->SetLabel(feelsLikeStr);
        }

        if (m_Settings.includeHighLow)
        {
            int high = static_cast<int>(m_Settings.celsius ? forecast.forecastday[0].day.maxtemp_c : forecast.forecastday[0].day.maxtemp_f);
            int low = static_cast<int>(m_Settings.celsius ? forecast.forecastday[0].day.mintemp_c : forecast.forecastday[0].day.mintemp_f);
            wxString hiLowStr = wxString::Format("H: %d° L: %d°", high, low);
            m_HiLowLabel->SetLabel(hiLowStr);
        }

        m_WeatherAPI.GetConditionIcon(curr.condition, [this](const wxImage& icon) {
            if (icon.IsOk()) {
                auto s = icon.GetSize();
                m_WeatherIcon->SetBitmap(icon);

                Layout();
                SendSizeEventToParent();
            }
            else {
                wxLogError("Failed to load weather icon.");
            }
            });
        });
}

void weather::CurrentWeatherTile::CreateNormalLayout()
{
    m_WeatherIcon = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    m_MainSizer->Add(m_WeatherIcon, 0, wxRIGHT, 2);

    m_TemperatureLabel = new wxStaticText(this, wxID_ANY, "--°");
    m_TemperatureLabel->SetFont(wxFont(26, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    m_MainSizer->Add(m_TemperatureLabel, 0, wxRIGHT | wxALIGN_CENTRE_VERTICAL, 4);

    wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
    m_MainSizer->Add(infoSizer, 1, wxALIGN_CENTRE_VERTICAL);

    m_ConditionLabel = new wxStaticText(this, wxID_ANY, "Loading...");
    m_ConditionLabel->SetFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    infoSizer->Add(m_ConditionLabel, 0, wxRIGHT, 4);

    if (m_Settings.includeFeelsLike)
    {
        m_FeelsLikeLabel = new wxStaticText(this, wxID_ANY, "Loading...");
        m_FeelsLikeLabel->SetFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        infoSizer->Add(m_FeelsLikeLabel, 0, wxRIGHT, 4);
    }

    if (m_Settings.includeHighLow)
    {
        m_HiLowLabel = new wxStaticText(this, wxID_ANY, "Loading...");
        m_HiLowLabel->SetFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        infoSizer->Add(m_HiLowLabel, 0, wxRIGHT, 4);
    }

}

void weather::CurrentWeatherTile::CreateCompactLayout()
{
    m_WeatherIcon = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    m_MainSizer->Add(m_WeatherIcon, 0, wxRIGHT, 4);

    wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
    m_MainSizer->Add(infoSizer, 1, wxALIGN_CENTRE_VERTICAL);

    m_ConditionLabel = new wxStaticText(this, wxID_ANY, "Loading...");
    infoSizer->Add(m_ConditionLabel, 0, wxRIGHT, 4);

    m_TemperatureLabel = new wxStaticText(this, wxID_ANY, "--°");
    m_TemperatureLabel->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    infoSizer->Add(m_TemperatureLabel, 0, wxRIGHT, 4);

    if (m_Settings.includeFeelsLike)
    {
        m_FeelsLikeLabel = new wxStaticText(this, wxID_ANY, "Loading...");
        m_FeelsLikeLabel->SetFont(wxFont(6, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        infoSizer->Add(m_FeelsLikeLabel, 0, wxRIGHT, 4);
    }

    if (m_Settings.includeHighLow)
    {
        m_HiLowLabel = new wxStaticText(this, wxID_ANY, "Loading...");
        m_HiLowLabel->SetFont(wxFont(6, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        infoSizer->Add(m_HiLowLabel, 0, wxRIGHT, 4);
    }
}