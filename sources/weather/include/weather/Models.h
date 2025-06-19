#pragma once

#include <nlohmann/json.hpp>

#include <string>

namespace weather
{
    struct SearchLocation
    {
        int id;
        std::string name;
        std::string region;
        std::string country;
        double lat;
        double lon;
        std::string url;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SearchLocation, id, name, region, country, lat, lon, url);

    //struct SearchResults
    //{
    //    std::vector<weather::SearchLocation> locations;
    //};
    //NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SearchResults, locations);

    struct Location
    {
        std::string name;
        std::string region;
        std::string country;
        double lat;
        double lon;
        std::string tz_id;
        int localtime_epoch;
        std::string localtime;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Location, name, region, country, lat, lon, tz_id, localtime_epoch, localtime);

    struct Condition
    {
        int code;
        std::string icon;
        std::string text;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Condition, code, icon, text);

    struct Current
    {
        int last_updated_epoch;
        std::string last_updated;
        double temp_c;
        double temp_f;
        int is_day;
        weather::Condition condition;
        double wind_mph;
        double wind_kph;
        int wind_degree;
        std::string wind_dir;
        double pressure_mb;
        double pressure_in;
        double precip_mm;
        double precip_in;
        double humidity;
        double cloud;
        double feelslike_c;
        double feelslike_f;
        double windchill_c;
        double windchill_f;
        double heatindex_c;
        double heatindex_f;
        double dewpoint_c;
        double dewpoint_f;
        double vis_km;
        double vis_miles;
        double uv;
        double gust_mph;
        double gust_kph;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Current, last_updated_epoch, last_updated, temp_c, temp_f, is_day, condition,
        wind_mph, wind_kph, wind_degree, wind_dir, pressure_mb, pressure_in,
        precip_mm, precip_in, humidity, cloud, feelslike_c, feelslike_f,
        windchill_c, windchill_f, heatindex_c, heatindex_f,
        dewpoint_c, dewpoint_f, vis_km, vis_miles, uv, gust_mph, gust_kph);


    struct Day
    {
        double maxtemp_c;
        double maxtemp_f;
        double mintemp_c;
        double mintemp_f;
        double avgtemp_c;
        double avgtemp_f;
        double maxwind_mph;
        double maxwind_kph;
        double totalprecip_mm;
        double totalprecip_in;
        double totalsnow_cm;
        double avgvis_km;
        double avgvis_miles;
        int avghumidity;
        int daily_will_it_rain;
        int daily_chance_of_rain;
        int daily_will_it_snow;
        int daily_chance_of_snow;
        weather::Condition condition;
        double uv;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Day, maxtemp_c, maxtemp_f, mintemp_c, mintemp_f, avgtemp_c, avgtemp_f, maxwind_mph,
        maxwind_kph, totalprecip_mm, totalprecip_in, totalsnow_cm, avgvis_km, avgvis_miles, avghumidity, daily_will_it_rain,
        daily_chance_of_rain, daily_will_it_snow, daily_chance_of_snow, condition, uv);

    struct Astro
    {
        std::string sunrise;
        std::string sunset;
        std::string moonrise;
        std::string moonset;
        std::string moon_phase;
        int moon_illumination;
        int is_moon_up;
        int is_sun_up;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Astro, sunrise, sunset, moonrise, moonset, moon_phase, moon_illumination, is_moon_up, is_sun_up);

    struct Hour
    {
        int time_epoch;
        std::string time;
        double temp_c;
        double temp_f;
        int is_day;
        weather::Condition condition;
        double wind_mph;
        double wind_kph;
        double wind_degree;
        std::string wind_dir;
        double pressure_mb;
        double pressure_in;
        double precip_mm;
        double precip_in;
        double snow_cm;
        int humidity;
        int cloud;
        double feelslike_c;
        double feelslike_f;
        double windchill_c;
        double windchill_f;
        double heatindex_c;
        double heatindex_f;
        double dewpoint_c;
        double dewpoint_f;
        int will_it_rain;
        int chance_of_rain;
        int will_it_snow;
        int chance_of_snow;
        double vis_km;
        double vis_miles;
        double gust_mph;
        double gust_kph;
        int uv;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Hour, time_epoch, time, temp_c, temp_f, is_day, condition, wind_mph, wind_kph, wind_degree,
        wind_dir, pressure_mb, pressure_in, precip_mm, precip_in, snow_cm, humidity, cloud,
        feelslike_c, feelslike_f, windchill_c, windchill_f, heatindex_c, heatindex_f,
        dewpoint_c, dewpoint_f, will_it_rain, chance_of_rain, will_it_snow,
        chance_of_snow, vis_km, vis_miles, gust_mph, gust_kph, uv);

    struct Forecastday
    {
        std::string date;
        int date_epoch;
        weather::Day day;
        weather::Astro astro;
        std::vector<weather::Hour> hour;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Forecastday, date, date_epoch, day, astro, hour);

    struct Forecast
    {
        std::vector<weather::Forecastday> forecastday;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Forecast, forecastday);
}