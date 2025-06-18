#pragma once

#include "weather/Models.h"

#include <wx/event.h>

namespace weather
{
    class WeatherAPI : public wxEvtHandler
    {
    public:
        WeatherAPI(const std::string& apiKey);
        ~WeatherAPI();

        using CurrentWeatherCallback = std::function<void(const weather::Current& currentWeather, const weather::Location& location)>;
        bool GetCurrentWeather(const std::string& location, CurrentWeatherCallback callback);

        using ConditionIconCallback = std::function<void(const wxImage& icon)>;
        bool GetConditionIcon(const weather::Condition& currentCondition, ConditionIconCallback callback);

        using ForecastCallback = std::function<void(const weather::Forecast& forecast, const weather::Current& currentWeather, const weather::Location& location)>;
        bool GetForecast(const std::string& location, int days, ForecastCallback callback);

    private:
        std::string m_ApiKey;
    };
}