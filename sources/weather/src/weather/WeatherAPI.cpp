#include "weather/WeatherAPI.h"

#include <nlohmann/json.hpp>

#include <wx/webrequest.h>
#include <wx/log.h>
#include <wx/image.h>

weather::WeatherAPI::WeatherAPI(const std::string& apiKey) :
    m_ApiKey(apiKey)
{

}

weather::WeatherAPI::~WeatherAPI()
{

}

bool weather::WeatherAPI::GetCurrentWeather(const std::string& location, CurrentWeatherCallback callback)
{
    std::string url = "http://api.weatherapi.com/v1/current.json?key=" + m_ApiKey + "&q=" + location + "&aqi=no";

    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(this, url);

    if (request.IsOk())
    {
        Bind(wxEVT_WEBREQUEST_STATE, [callback](wxWebRequestEvent& evt) {
            switch (evt.GetState())
            {
            case wxWebRequest::State_Completed:
            {
                char* buffer = new char[evt.GetResponse().GetStream()->GetSize() + 1];
                if (evt.GetResponse().GetStream()->ReadAll(buffer, evt.GetResponse().GetStream()->GetSize()))
                {
                    buffer[evt.GetResponse().GetStream()->GetSize()] = '\0';
                    nlohmann::json responseJson = nlohmann::json::parse(buffer);
                    weather::Location loc = responseJson["location"];
                    weather::Current curr = responseJson["current"];

                    callback(curr, loc );
                }
                delete[] buffer;


                break;
            }
            case wxWebRequest::State_Failed:
                wxLogError("Request for current weather failed: %s", evt.GetErrorDescription());
                break;
            }  });

            request.Start();
    }
    else
    {
        return false;
    }

    return true;
}

bool weather::WeatherAPI::GetConditionIcon(const weather::Condition& currentCondition, ConditionIconCallback callback)
{
    if (currentCondition.icon.empty())
        return false;

    std::string url = "http:" + currentCondition.icon;

    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(this, url);

    if (request.IsOk())
    {
        Bind(wxEVT_WEBREQUEST_STATE, [callback](wxWebRequestEvent& evt) {
            switch (evt.GetState())
            {
            case wxWebRequest::State_Completed:
            {
                wxImage logoImage(*evt.GetResponse().GetStream());
                if (logoImage.IsOk())
                    callback(logoImage);

                break;
            }
            case wxWebRequest::State_Failed:
                wxLogError("Request for current weather failed: %s", evt.GetErrorDescription());
                break;
            }  });

            request.Start();
    }
    else
    {
        return false;
    }

    return true;
}

bool weather::WeatherAPI::GetForecast(const std::string& location, int days, ForecastCallback callback)
{
    wxString url = wxString::Format("http://api.weatherapi.com/v1/forecast.json?key=%s&q=%s&days=%d&aqi=no&alerts=no", m_ApiKey, location, days );

    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(this, url);

    if (request.IsOk())
    {
        Bind(wxEVT_WEBREQUEST_STATE, [callback](wxWebRequestEvent& evt) {
            switch (evt.GetState())
            {
            case wxWebRequest::State_Completed:
            {
                char* buffer = new char[evt.GetResponse().GetStream()->GetSize() + 1];
                if (evt.GetResponse().GetStream()->ReadAll(buffer, evt.GetResponse().GetStream()->GetSize()))
                {
                    buffer[evt.GetResponse().GetStream()->GetSize()] = '\0';
                    nlohmann::json responseJson = nlohmann::json::parse(buffer);
                    weather::Location loc = responseJson["location"];
                    weather::Current curr = responseJson["current"];
                    weather::Forecast forecast = responseJson["forecast"];

                    callback(forecast, curr, loc );
                }
                delete[] buffer;

                break;
            }
            case wxWebRequest::State_Failed:
                wxLogError("Request for current weather failed: %s", evt.GetErrorDescription());
                break;
            }  });

            request.Start();
    }
    else
    {
        return false;
    }

    return true;
}

bool weather::WeatherAPI::SearchLocation(const std::string& query, weather::WeatherAPI::SearchLocationCallback callback)
{
    wxString url = wxString::Format("http://api.weatherapi.com/v1/search.json?key=%s&q=%s", m_ApiKey, query);

    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(this, url);

    if (request.IsOk())
    {
        Bind(wxEVT_WEBREQUEST_STATE, [callback](wxWebRequestEvent& evt) {
            switch (evt.GetState())
            {
            case wxWebRequest::State_Completed:
            {
                char* buffer = new char[evt.GetResponse().GetStream()->GetSize() + 1];
                if (evt.GetResponse().GetStream()->ReadAll(buffer, evt.GetResponse().GetStream()->GetSize()))
                {
                    buffer[evt.GetResponse().GetStream()->GetSize()] = '\0';
                    nlohmann::json responseJson = nlohmann::json::parse(buffer);
                    auto locations = responseJson.get<std::vector<weather::SearchLocation>>();
                    callback(locations);
                }
                delete[] buffer;

                break;
            }
            case wxWebRequest::State_Failed:
                wxLogError("Request for current weather failed: %s", evt.GetErrorDescription());
                break;
            }  });

            request.Start();
    }
    else
    {
        return false;
    }

    return true;
}

//bool weather::WeatherAPI::IPLookup()
//{
//
//}