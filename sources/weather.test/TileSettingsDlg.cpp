#include "TileSettingsDlg.h"

#include <wx/wx.h>

TileSettingsDlg::TileSettingsDlg(wxWindow* parent, weather::CurrentWeatherTile::Settings& settings) :
    wxDialog(parent, wxID_ANY, "Tile Settings", wxDefaultPosition, wxSize(300, 200)),
    m_Settings(settings)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    m_ShowCompact = new wxCheckBox(this, wxID_ANY, "Compact Layout");
    m_ShowCompact->SetValue(m_Settings.style == weather::CurrentWeatherTile::TileStyle::Compact );
    mainSizer->Add(m_ShowCompact, 0, wxALL, 2);

    m_ShowFeelsLike = new wxCheckBox(this, wxID_ANY, "Show Feels Like");
    m_ShowFeelsLike->SetValue(m_Settings.includeFeelsLike);
    mainSizer->Add(m_ShowFeelsLike, 0, wxALL, 2);

    m_ShowHighLow = new wxCheckBox(this, wxID_ANY, "Show High and Low");
    m_ShowHighLow->SetValue(m_Settings.includeHighLow);
    mainSizer->Add(m_ShowHighLow, 0, wxALL, 2);

    m_UseCelsius = new wxCheckBox(this, wxID_ANY, "Use Celsius");
    m_UseCelsius->SetValue(m_Settings.celsius);
    mainSizer->Add(m_UseCelsius, 0, wxALL, 2);

    wxBoxSizer* buttonRow = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okButton = new wxButton(this, wxID_OK, "OK");
    okButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        m_Settings.style = m_ShowCompact->GetValue() ? weather::CurrentWeatherTile::TileStyle::Compact : weather::CurrentWeatherTile::TileStyle::Normal;
        m_Settings.includeFeelsLike = m_ShowFeelsLike->GetValue();
        m_Settings.includeHighLow = m_ShowHighLow->GetValue();
        m_Settings.celsius = m_UseCelsius->GetValue();
        EndModal(wxID_OK);
    });

    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");
    buttonRow->Add(okButton, 0, wxRIGHT, 5);
    buttonRow->Add(cancelButton, 0);
    mainSizer->Add(buttonRow, 0, wxALIGN_RIGHT | wxALL, 5);

    SetSizerAndFit(mainSizer);
}
