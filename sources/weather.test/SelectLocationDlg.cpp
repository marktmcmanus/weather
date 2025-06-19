#include "SelectLocationDlg.h"

#include <wx/wx.h>

#include <format>

SelectLocationDlg::SelectLocationDlg(wxWindow* parent, weather::WeatherAPI& weatherApi) :
    wxDialog(parent, wxID_ANY, "Search Location"),
    m_WeatherApi(weatherApi)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    m_SearchText = new wxTextCtrl(this, wxID_ANY, "");
    m_SearchText->SetHint("Search for a location...");
    m_SearchText->Bind(wxEVT_TEXT, &SelectLocationDlg::OnSearch, this);
    sizer->Add(m_SearchText, 0, wxEXPAND | wxALL, 5);

    m_SearchResultsList = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
    sizer->Add(m_SearchResultsList, 0, wxEXPAND | wxALL, 5);

    wxBoxSizer* buttonRow = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okButton = new wxButton(this, wxID_OK, "OK");
    okButton->SetDefault();
    okButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        m_SelectedLocation = m_SearchResults[m_SearchResultsList->GetSelection()];
        EndModal(wxID_OK);
        });
    okButton->Bind(wxEVT_UPDATE_UI, [this](wxUpdateUIEvent& evt) {
        evt.Enable(m_SearchResultsList->GetSelection() != wxNOT_FOUND);
        });

    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");
    buttonRow->Add(okButton, 0, wxRIGHT, 5);
    buttonRow->Add(cancelButton, 0);
    sizer->Add(buttonRow, 0, wxALIGN_RIGHT | wxALL, 5);

    SetSizerAndFit(sizer);
}

void SelectLocationDlg::OnSearch(wxCommandEvent& evt)
{
    wxString searchText = evt.GetString().Trim().Trim(false);
    if (searchText.empty())
    {
        m_SearchResultsList->Clear();
        m_SearchResults.clear();
        return;
    }

    m_WeatherApi.SearchLocation(searchText.ToStdString(), [this](const std::vector<weather::SearchLocation> locations) {
        m_SearchResults = locations;
        UpdateSearchResults(locations);
        });
}

void SelectLocationDlg::UpdateSearchResults(const std::vector<weather::SearchLocation>& results)
{
    m_SearchResultsList->Clear();
    for (const auto& location : results)
    {
        std::vector<std::string> parts({ location.name, location.region, location.country });
        std::string displayName;
        for (const auto& part : parts)
        {
            if (!part.empty())
            {
                if (!displayName.empty())
                {
                    displayName += ", ";
                }
                displayName += part;
            }
        }
        m_SearchResultsList->Append(displayName);
    }
}