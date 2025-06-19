#pragma once

#include <weather/WeatherAPI.h>
#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/textctrl.h>
#include <wx/weakref.h>

class SelectLocationDlg : public wxDialog
{
public:
    SelectLocationDlg(wxWindow* parent, weather::WeatherAPI& weatherApi);
    virtual ~SelectLocationDlg() = default;

    std::optional<weather::SearchLocation> GetSelectedLocation() const { return m_SelectedLocation; }

private:
    void OnSearch(wxCommandEvent& event);
    void UpdateSearchResults(const std::vector<weather::SearchLocation>& results);

    weather::WeatherAPI& m_WeatherApi;

    wxWeakRef<wxTextCtrl> m_SearchText;
    wxWeakRef<wxListBox> m_SearchResultsList;

    std::vector<weather::SearchLocation> m_SearchResults;
    std::optional<weather::SearchLocation> m_SelectedLocation;
};