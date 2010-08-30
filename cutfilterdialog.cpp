/*****************************************************************************\
 *                        ANALYSIS PERFORMANCE TOOLS                         *
 *                                  wxparaver                                *
 *              Paraver Trace Visualization and Analysis Tool                *
 *****************************************************************************
 *     ___     This library is free software; you can redistribute it and/or *
 *    /  __         modify it under the terms of the GNU LGPL as published   *
 *   /  /  _____    by the Free Software Foundation; either version 2.1      *
 *  /  /  /     \   of the License, or (at your option) any later version.   *
 * (  (  ( B S C )                                                           *
 *  \  \  \_____/   This library is distributed in hope that it will be      *
 *   \  \__         useful but WITHOUT ANY WARRANTY; without even the        *
 *    \___          implied warranty of MERCHANTABILITY or FITNESS FOR A     *
 *                  PARTICULAR PURPOSE. See the GNU LGPL for more details.   *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this library; if not, write to the Free Software Foundation,   *
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA          *
 * The GNU LEsser General Public License is contained in the file COPYING.   *
 *                                 ---------                                 *
 *   Barcelona Supercomputing Center - Centro Nacional de Supercomputacion   *
\*****************************************************************************/

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- *\
 | @file: $HeadURL$
 | @last_commit: $Date$
 | @version:     $Revision$
\* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "cutfilterdialog.h"
#include "paraverconfig.h"
#include "kernelconnection.h"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <wx/filedlg.h>

////@begin XPM images
#include "arrow_up.xpm"
#include "arrow_down.xpm"
////@end XPM images




/*!
 * CutFilterDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CutFilterDialog, wxDialog )


/*!
 * CutFilterDialog event table definition
 */

BEGIN_EVENT_TABLE( CutFilterDialog, wxDialog )

////@begin CutFilterDialog event table entries
  EVT_FILEPICKER_CHANGED( ID_FILECTRL_CUTFILTER_TRACE_SELECTION, CutFilterDialog::OnFilectrlTracePickerChanged )

  EVT_LISTBOX( ID_CHECKLISTBOX, CutFilterDialog::OnCheckListToolOrderSelected )
  EVT_UPDATE_UI( ID_CHECKLISTBOX, CutFilterDialog::OnCheckListToolOrderUpdate )

  EVT_BUTTON( ID_BITMAPBUTTON_PUSH_UP, CutFilterDialog::OnBitmapbuttonPushUpClick )

  EVT_BUTTON( ID_BITMAPBUTTON_PUSH_DOWN, CutFilterDialog::OnBitmapbuttonPushDownClick )

  EVT_NOTEBOOK_PAGE_CHANGED( ID_NOTEBOOK_CUT_FILTER_OPTIONS, CutFilterDialog::OnNotebookCutFilterOptionsPageChanged )

  EVT_BUTTON( ID_BUTTON_CUTTER_ALL_TRACE, CutFilterDialog::OnButtonCutterAllTraceClick )

  EVT_CHECKBOX( ID_CHECKBOX_CHECK_CUTTER_ORIGINAL_TIME, CutFilterDialog::OnCheckOriginalTimeClick )

  EVT_UPDATE_UI( ID_PANEL_FILTER, CutFilterDialog::OnPanelFilterUpdate )

  EVT_UPDATE_UI( ID_PANEL_SOFTWARE_COUNTERS, CutFilterDialog::OnPanelSoftwareCountersUpdate )

  EVT_BUTTON( wxID_OK, CutFilterDialog::OnOkClick )

////@end CutFilterDialog event table entries

END_EVENT_TABLE()


/*!
 * CutFilterDialog constructors
 */

CutFilterDialog::CutFilterDialog()
{
  Init();
}

CutFilterDialog::CutFilterDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
  Init();
  Create(parent, id, caption, pos, size, style);
}


/*!
 * CutFilterDialog creator
 */

bool CutFilterDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CutFilterDialog creation
  SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
  wxDialog::Create( parent, id, caption, pos, size, style );

  CreateControls();
  if (GetSizer())
  {
    GetSizer()->SetSizeHints(this);
  }
  Centre();
////@end CutFilterDialog creation
  return true;
}


/*!
 * CutFilterDialog destructor
 */

CutFilterDialog::~CutFilterDialog()
{
////@begin CutFilterDialog destruction
////@end CutFilterDialog destruction
}


/*!
 * Member initialisation
 */

void CutFilterDialog::Init()
{
////@begin CutFilterDialog member initialisation
  traceOptions = NULL;
  filePickerTrace = NULL;
  loadResultingTrace = NULL;
  checkListToolOrder = NULL;
  buttonUp = NULL;
  buttonDown = NULL;
  notebookTools = NULL;
  radioCutterCutByTime = NULL;
  radioCutterCutByTimePercent = NULL;
  textCutterBeginCut = NULL;
  textCutterEndCut = NULL;
  textCutterTasks = NULL;
  buttonCutterSelectRegion = NULL;
  buttonCutterAllTrace = NULL;
  checkCutterUseOriginalTime = NULL;
  checkCutterRemoveFirstState = NULL;
  checkCutterBreakStates = NULL;
  checkCutterRemoveLastState = NULL;
  textCutterMaximumTraceSize = NULL;
  checkFilterDiscardStateRecords = NULL;
  checkFilterDiscardEventRecords = NULL;
  checkFilterDiscardCommunicationRecords = NULL;
  staticBoxSizerFilterStates = NULL;
  checkListFilterStates = NULL;
  buttonFilterSelectAll = NULL;
  buttonFilterUnselectAll = NULL;
  buttonFilterSetMinimumTime = NULL;
  checkFilterDiscardListedStates = NULL;
  staticBoxSizerFilterEvents = NULL;
  listboxFilterEvents = NULL;
  buttonFilterAdd = NULL;
  buttonFilterDelete = NULL;
  checkFilterDiscardListedEvents = NULL;
  staticBoxSizerFilterCommunications = NULL;
  staticTextFilterSize = NULL;
  textFilterSize = NULL;
  staticTextFilterSizeUnit = NULL;
  radioSCOnIntervals = NULL;
  radioSCOnStates = NULL;
  staticTextSCSamplingInterval = NULL;
  textSCSamplingInterval = NULL;
  staticTextSCMinimumBurstTime = NULL;
  textSCMinimumBurstTime = NULL;
  checkListSCSelectedEvents = NULL;
  buttonSCSelectedEventsAdd = NULL;
  buttonSCSelectedEventsDelete = NULL;
  radioSCCountEvents = NULL;
  radioSCAccumulateValues = NULL;
  checkSCRemoveStates = NULL;
  checkSCSummarizeUseful = NULL;
  checkSCGlobalCounters = NULL;
  checkSCOnlyInBurstsCounting = NULL;
  listSCKeepEvents = NULL;
  buttonSCKeepEventsAdd = NULL;
  buttonSCKeepEventsDelete = NULL;
////@end CutFilterDialog member initialisation
}


/*!
 * Control creation for CutFilterDialog
 */

void CutFilterDialog::CreateControls()
{    
////@begin CutFilterDialog content construction
  CutFilterDialog* itemDialog1 = this;

  wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
  itemDialog1->SetSizer(itemBoxSizer2);

  wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer2->Add(itemBoxSizer3, 1, wxGROW|wxALL, 5);

  wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
  itemBoxSizer3->Add(itemBoxSizer4, 5, wxALIGN_TOP|wxALL, 3);

  wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _("Trace"), wxDefaultPosition, wxDefaultSize, 0 );
  if (CutFilterDialog::ShowToolTips())
    itemStaticText5->SetToolTip(_("Trace that will be used by the Cut/Filter toolkit."));
  itemBoxSizer4->Add(itemStaticText5, 0, wxALIGN_LEFT|wxALL, 5);

  filePickerTrace = new wxFilePickerCtrl( itemDialog1, ID_FILECTRL_CUTFILTER_TRACE_SELECTION, wxEmptyString, _("Trace to Cut/Filter"), _T("Paraver trace (*.prv;*.prv.gz)|*.prv;*.prv.gz|All files (*.*)|*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_OPEN|wxFLP_FILE_MUST_EXIST|wxFLP_CHANGE_DIR );
  if (CutFilterDialog::ShowToolTips())
    filePickerTrace->SetToolTip(_("Trace that will be used by the Cut/Filter toolkit."));
  itemBoxSizer4->Add(filePickerTrace, 2, wxGROW|wxALL, 5);

  loadResultingTrace = new wxCheckBox( itemDialog1, ID_CHECKBOX_LOAD_RESULTING_TRACE, _("Load the resulting trace"), wxDefaultPosition, wxDefaultSize, 0 );
  loadResultingTrace->SetValue(false);
  itemBoxSizer4->Add(loadResultingTrace, 0, wxGROW|wxALL, 5);

  wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer4->Add(itemBoxSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

  wxButton* itemButton9 = new wxButton( itemDialog1, ID_BUTTON, _("Load XML..."), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer8->Add(itemButton9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxButton* itemButton10 = new wxButton( itemDialog1, ID_BUTTON1, _("Save XML..."), wxDefaultPosition, wxDefaultSize, 0 );
  itemButton10->Enable(false);
  itemBoxSizer8->Add(itemButton10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxBoxSizer* itemBoxSizer11 = new wxBoxSizer(wxVERTICAL);
  itemBoxSizer3->Add(itemBoxSizer11, 3, wxGROW, 5);

  wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _("  Ordered execution"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer11->Add(itemStaticText12, 0, wxALIGN_LEFT|wxALL, 5);

  wxBoxSizer* itemBoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer11->Add(itemBoxSizer13, 3, wxGROW|wxALL, 3);

  wxArrayString checkListToolOrderStrings;
  checkListToolOrder = new wxCheckListBox( itemDialog1, ID_CHECKLISTBOX, wxDefaultPosition, wxDefaultSize, checkListToolOrderStrings, wxLB_SINGLE|wxLB_NEEDED_SB );
  if (CutFilterDialog::ShowToolTips())
    checkListToolOrder->SetToolTip(_("Select the order of the Cut/Filter tools."));
  itemBoxSizer13->Add(checkListToolOrder, 3, wxGROW|wxLEFT|wxTOP, 5);

  wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxVERTICAL);
  itemBoxSizer13->Add(itemBoxSizer15, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

  buttonUp = new wxBitmapButton( itemDialog1, ID_BITMAPBUTTON_PUSH_UP, itemDialog1->GetBitmapResource(wxT("arrow_up.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
  if (CutFilterDialog::ShowToolTips())
    buttonUp->SetToolTip(_("Select the order of the Cut/Filter tools."));
  itemBoxSizer15->Add(buttonUp, 1, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM, 5);

  buttonDown = new wxBitmapButton( itemDialog1, ID_BITMAPBUTTON_PUSH_DOWN, itemDialog1->GetBitmapResource(wxT("arrow_down.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
  if (CutFilterDialog::ShowToolTips())
    buttonDown->SetToolTip(_("Select the order of the Cut/Filter tools."));
  itemBoxSizer15->Add(buttonDown, 1, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM, 5);

  notebookTools = new wxNotebook( itemDialog1, ID_NOTEBOOK_CUT_FILTER_OPTIONS, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

  wxPanel* itemPanel19 = new wxPanel( notebookTools, ID_PANEL_CUTTER, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  wxBoxSizer* itemBoxSizer20 = new wxBoxSizer(wxVERTICAL);
  itemPanel19->SetSizer(itemBoxSizer20);

  wxStaticBox* itemStaticBoxSizer21Static = new wxStaticBox(itemPanel19, wxID_STATIC, _(" Trace Limits "));
  wxStaticBoxSizer* itemStaticBoxSizer21 = new wxStaticBoxSizer(itemStaticBoxSizer21Static, wxVERTICAL);
  itemBoxSizer20->Add(itemStaticBoxSizer21, 0, wxGROW|wxALL, 5);
  wxBoxSizer* itemBoxSizer22 = new wxBoxSizer(wxHORIZONTAL);
  itemStaticBoxSizer21->Add(itemBoxSizer22, 0, wxGROW|wxLEFT|wxTOP, 5);
  wxBoxSizer* itemBoxSizer23 = new wxBoxSizer(wxVERTICAL);
  itemBoxSizer22->Add(itemBoxSizer23, 1, wxGROW|wxLEFT|wxTOP, 5);
  radioCutterCutByTime = new wxRadioButton( itemPanel19, ID_RADIOBUTTON_CUTTER_CUT_BY_TIME, _("Cut by time"), wxDefaultPosition, wxDefaultSize, 0 );
  radioCutterCutByTime->SetValue(true);
  itemBoxSizer23->Add(radioCutterCutByTime, 1, wxALIGN_LEFT|wxLEFT|wxTOP, 5);

  radioCutterCutByTimePercent = new wxRadioButton( itemPanel19, ID_RADIOBUTTON_CUTTER_CUT_BY_PERCENT, _("Cut by time %"), wxDefaultPosition, wxDefaultSize, 0 );
  radioCutterCutByTimePercent->SetValue(false);
  itemBoxSizer23->Add(radioCutterCutByTimePercent, 1, wxALIGN_LEFT|wxLEFT|wxTOP, 5);

  wxBoxSizer* itemBoxSizer26 = new wxBoxSizer(wxVERTICAL);
  itemBoxSizer22->Add(itemBoxSizer26, 2, wxGROW|wxLEFT|wxRIGHT|wxTOP, 5);
  wxBoxSizer* itemBoxSizer27 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer26->Add(itemBoxSizer27, 0, wxGROW|wxLEFT|wxTOP, 5);
  wxStaticText* itemStaticText28 = new wxStaticText( itemPanel19, wxID_STATIC, _("Begin"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer27->Add(itemStaticText28, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

  textCutterBeginCut = new wxTextCtrl( itemPanel19, ID_TEXTCTRL_CUTTER_BEGIN_CUT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer27->Add(textCutterBeginCut, 3, wxGROW|wxLEFT|wxTOP|wxBOTTOM, 5);

  wxBoxSizer* itemBoxSizer30 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer26->Add(itemBoxSizer30, 0, wxGROW|wxLEFT|wxTOP, 5);
  wxStaticText* itemStaticText31 = new wxStaticText( itemPanel19, wxID_STATIC, _("End"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer30->Add(itemStaticText31, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

  textCutterEndCut = new wxTextCtrl( itemPanel19, ID_TEXTCTRL_CUTTER_END_CUT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer30->Add(textCutterEndCut, 3, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

  wxStaticLine* itemStaticLine33 = new wxStaticLine( itemPanel19, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
  itemStaticBoxSizer21->Add(itemStaticLine33, 0, wxGROW|wxALL, 5);

  wxBoxSizer* itemBoxSizer34 = new wxBoxSizer(wxHORIZONTAL);
  itemStaticBoxSizer21->Add(itemBoxSizer34, 0, wxGROW|wxALL, 5);
  wxStaticText* itemStaticText35 = new wxStaticText( itemPanel19, wxID_STATIC, _("Tasks"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer34->Add(itemStaticText35, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  textCutterTasks = new wxTextCtrl( itemPanel19, ID_TEXTCTRL_CUTTER_TASKS, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  if (CutFilterDialog::ShowToolTips())
    textCutterTasks->SetToolTip(_("Select the list of tasks to cut, separated by commas. Ranges marked with \"-\" are allowed. I.e. \"1-50,60,70-100\"."));
  itemBoxSizer34->Add(textCutterTasks, 1, wxGROW|wxALL, 5);

  wxStaticLine* itemStaticLine37 = new wxStaticLine( itemPanel19, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
  itemStaticBoxSizer21->Add(itemStaticLine37, 0, wxGROW|wxALL, 5);

  wxBoxSizer* itemBoxSizer38 = new wxBoxSizer(wxHORIZONTAL);
  itemStaticBoxSizer21->Add(itemBoxSizer38, 0, wxGROW|wxALL, 5);
  buttonCutterSelectRegion = new wxButton( itemPanel19, ID_BUTTON_CUTTER_SELECT_REGION, _("Select Region..."), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer38->Add(buttonCutterSelectRegion, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, 5);

  buttonCutterAllTrace = new wxButton( itemPanel19, ID_BUTTON_CUTTER_ALL_TRACE, _("All Trace"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer38->Add(buttonCutterAllTrace, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, 5);

  wxStaticBox* itemStaticBoxSizer41Static = new wxStaticBox(itemPanel19, wxID_STATIC, _(" Trace Options "));
  wxStaticBoxSizer* itemStaticBoxSizer41 = new wxStaticBoxSizer(itemStaticBoxSizer41Static, wxVERTICAL);
  itemBoxSizer20->Add(itemStaticBoxSizer41, 0, wxGROW|wxALL, 5);
  wxBoxSizer* itemBoxSizer42 = new wxBoxSizer(wxHORIZONTAL);
  itemStaticBoxSizer41->Add(itemBoxSizer42, 0, wxGROW|wxLEFT|wxTOP, 5);
  checkCutterUseOriginalTime = new wxCheckBox( itemPanel19, ID_CHECKBOX_CHECK_CUTTER_ORIGINAL_TIME, _("Use original time"), wxDefaultPosition, wxDefaultSize, 0 );
  checkCutterUseOriginalTime->SetValue(false);
  itemBoxSizer42->Add(checkCutterUseOriginalTime, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, 5);

  checkCutterRemoveFirstState = new wxCheckBox( itemPanel19, ID_CHECKBOX_CUTTER_REMOVE_FIRST_STATE, _("Remove first state"), wxDefaultPosition, wxDefaultSize, 0 );
  checkCutterRemoveFirstState->SetValue(false);
  itemBoxSizer42->Add(checkCutterRemoveFirstState, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, 5);

  wxBoxSizer* itemBoxSizer45 = new wxBoxSizer(wxHORIZONTAL);
  itemStaticBoxSizer41->Add(itemBoxSizer45, 0, wxGROW|wxLEFT|wxTOP|wxBOTTOM, 5);
  checkCutterBreakStates = new wxCheckBox( itemPanel19, ID_CHECKBOX_CUTTER_BREAK_STATES, _("Don't break states"), wxDefaultPosition, wxDefaultSize, 0 );
  checkCutterBreakStates->SetValue(false);
  itemBoxSizer45->Add(checkCutterBreakStates, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, 5);

  checkCutterRemoveLastState = new wxCheckBox( itemPanel19, ID_CHECKBOX_CUTTER_REMOVE_LAST_STATE, _("Remove last state"), wxDefaultPosition, wxDefaultSize, 0 );
  checkCutterRemoveLastState->SetValue(false);
  itemBoxSizer45->Add(checkCutterRemoveLastState, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, 5);

  wxStaticBox* itemStaticBoxSizer48Static = new wxStaticBox(itemPanel19, wxID_STATIC, _(" Output Trace "));
  wxStaticBoxSizer* itemStaticBoxSizer48 = new wxStaticBoxSizer(itemStaticBoxSizer48Static, wxHORIZONTAL);
  itemBoxSizer20->Add(itemStaticBoxSizer48, 0, wxGROW|wxALL, 5);
  wxStaticText* itemStaticText49 = new wxStaticText( itemPanel19, wxID_STATIC, _("Maximum trace size"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStaticBoxSizer48->Add(itemStaticText49, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  textCutterMaximumTraceSize = new wxSpinCtrl( itemPanel19, ID_SPINCTRL_CUTTER_MAXIMUM_SIZE, _T("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0 );
  itemStaticBoxSizer48->Add(textCutterMaximumTraceSize, 3, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxStaticText* itemStaticText51 = new wxStaticText( itemPanel19, wxID_STATIC, _("MB"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStaticBoxSizer48->Add(itemStaticText51, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  notebookTools->AddPage(itemPanel19, _("Cutter"));

  wxPanel* itemPanel52 = new wxPanel( notebookTools, ID_PANEL_FILTER, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  wxBoxSizer* itemBoxSizer53 = new wxBoxSizer(wxVERTICAL);
  itemPanel52->SetSizer(itemBoxSizer53);

  wxStaticBox* itemStaticBoxSizer54Static = new wxStaticBox(itemPanel52, wxID_STATIC, _(" Discard Records "));
  wxStaticBoxSizer* itemStaticBoxSizer54 = new wxStaticBoxSizer(itemStaticBoxSizer54Static, wxHORIZONTAL);
  itemBoxSizer53->Add(itemStaticBoxSizer54, 0, wxGROW|wxALL, 5);
  checkFilterDiscardStateRecords = new wxCheckBox( itemPanel52, ID_CHECKBOX_FILTER_DISCARD_STATE, _("State"), wxDefaultPosition, wxDefaultSize, 0 );
  checkFilterDiscardStateRecords->SetValue(false);
  itemStaticBoxSizer54->Add(checkFilterDiscardStateRecords, 0, wxGROW|wxALL, 5);

  checkFilterDiscardEventRecords = new wxCheckBox( itemPanel52, ID_CHECKBOX_FILTER_DISCARD_EVENT, _("Event"), wxDefaultPosition, wxDefaultSize, 0 );
  checkFilterDiscardEventRecords->SetValue(false);
  itemStaticBoxSizer54->Add(checkFilterDiscardEventRecords, 0, wxGROW|wxALL, 5);

  checkFilterDiscardCommunicationRecords = new wxCheckBox( itemPanel52, ID_CHECKBOX_FILTER_DISCARD_COMMUNICATION, _("Communication"), wxDefaultPosition, wxDefaultSize, 0 );
  checkFilterDiscardCommunicationRecords->SetValue(false);
  itemStaticBoxSizer54->Add(checkFilterDiscardCommunicationRecords, 0, wxGROW|wxALL, 5);

  staticBoxSizerFilterStates = new wxStaticBox(itemPanel52, wxID_STATIC, _(" States "));
  wxStaticBoxSizer* itemStaticBoxSizer58 = new wxStaticBoxSizer(staticBoxSizerFilterStates, wxHORIZONTAL);
  itemBoxSizer53->Add(itemStaticBoxSizer58, 1, wxGROW|wxALL, 5);
  wxArrayString checkListFilterStatesStrings;
  checkListFilterStatesStrings.Add(_("Idle; 0"));
  checkListFilterStatesStrings.Add(_("Running; 10000"));
  checkListFilterStatesStrings.Add(_("Not created; 0"));
  checkListFilterStatesStrings.Add(_("Waiting a message; 0"));
  checkListFilterStatesStrings.Add(_("Bloking Send; 0"));
  checkListFilterStatesStrings.Add(_("Thd. Synchr.; 0"));
  checkListFilterStatesStrings.Add(_("Test/Probe; 0"));
  checkListFilterStatesStrings.Add(_("Sched. and Fork/Join; 0"));
  checkListFilterStatesStrings.Add(_("Wait/WaitAll; 0"));
  checkListFilterStatesStrings.Add(_("Blocked; 0"));
  checkListFilterStatesStrings.Add(_("Inmediate Send; 0"));
  checkListFilterStatesStrings.Add(_("Inmediate Receive; 0"));
  checkListFilterStatesStrings.Add(_("I/O; 0"));
  checkListFilterStatesStrings.Add(_("Group Communication; 0"));
  checkListFilterStatesStrings.Add(_("Tracing Disabled; 0"));
  checkListFilterStatesStrings.Add(_("Others; 0"));
  checkListFilterStatesStrings.Add(_("Send Receive; 0"));
  checkListFilterStates = new wxCheckListBox( itemPanel52, ID_CHECKLISTBOX_FILTER_STATES, wxDefaultPosition, wxSize(-1, 100), checkListFilterStatesStrings, wxLB_SINGLE );
  itemStaticBoxSizer58->Add(checkListFilterStates, 2, wxGROW|wxALL, 5);

  wxBoxSizer* itemBoxSizer60 = new wxBoxSizer(wxVERTICAL);
  itemStaticBoxSizer58->Add(itemBoxSizer60, 1, wxGROW|wxALL, 5);
  buttonFilterSelectAll = new wxButton( itemPanel52, ID_BUTTON_FILTER_SELECT_ALL, _("Select all"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer60->Add(buttonFilterSelectAll, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM, 5);

  buttonFilterUnselectAll = new wxButton( itemPanel52, ID_BUTTON_FILTER_UNSELECT_ALL, _("Unselect all"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer60->Add(buttonFilterUnselectAll, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM, 5);

  buttonFilterSetMinimumTime = new wxButton( itemPanel52, ID_BUTTON_FILTER_SET_MINIMUM_TIME, _("Set min time"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer60->Add(buttonFilterSetMinimumTime, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM, 5);

  checkFilterDiscardListedStates = new wxCheckBox( itemPanel52, ID_CHECKBOX5, _("Discard"), wxDefaultPosition, wxDefaultSize, 0 );
  checkFilterDiscardListedStates->SetValue(false);
  itemBoxSizer60->Add(checkFilterDiscardListedStates, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

  staticBoxSizerFilterEvents = new wxStaticBox(itemPanel52, wxID_STATIC, _(" Events "));
  wxStaticBoxSizer* itemStaticBoxSizer65 = new wxStaticBoxSizer(staticBoxSizerFilterEvents, wxHORIZONTAL);
  itemBoxSizer53->Add(itemStaticBoxSizer65, 1, wxGROW|wxALL, 5);
  wxArrayString listboxFilterEventsStrings;
  listboxFilterEventsStrings.Add(_("42000059"));
  listboxFilterEventsStrings.Add(_("42000008"));
  listboxFilterEventsStrings.Add(_("50000001-50000003"));
  listboxFilterEvents = new wxListBox( itemPanel52, ID_LISTBOX_FILTER_EVENTS, wxDefaultPosition, wxDefaultSize, listboxFilterEventsStrings, wxLB_SINGLE );
  itemStaticBoxSizer65->Add(listboxFilterEvents, 2, wxGROW|wxALL, 5);

  wxBoxSizer* itemBoxSizer67 = new wxBoxSizer(wxVERTICAL);
  itemStaticBoxSizer65->Add(itemBoxSizer67, 1, wxGROW|wxALL, 5);
  buttonFilterAdd = new wxButton( itemPanel52, ID_BUTTON_FILTER_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer67->Add(buttonFilterAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM, 5);

  buttonFilterDelete = new wxButton( itemPanel52, ID_BUTTON_FILTER_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer67->Add(buttonFilterDelete, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM, 5);

  checkFilterDiscardListedEvents = new wxCheckBox( itemPanel52, ID_CHECKBOX_FILTER_DISCARD_LISTED_EVENTS, _("Discard"), wxDefaultPosition, wxDefaultSize, 0 );
  checkFilterDiscardListedEvents->SetValue(false);
  itemBoxSizer67->Add(checkFilterDiscardListedEvents, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

  staticBoxSizerFilterCommunications = new wxStaticBox(itemPanel52, wxID_STATIC, _(" Communications "));
  wxStaticBoxSizer* itemStaticBoxSizer71 = new wxStaticBoxSizer(staticBoxSizerFilterCommunications, wxHORIZONTAL);
  itemBoxSizer53->Add(itemStaticBoxSizer71, 0, wxGROW|wxALL, 5);
  staticTextFilterSize = new wxStaticText( itemPanel52, wxID_STATIC, _("Size"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStaticBoxSizer71->Add(staticTextFilterSize, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  textFilterSize = new wxSpinCtrl( itemPanel52, ID_SPINCTRL_FILTER_SIZE, _T("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
  itemStaticBoxSizer71->Add(textFilterSize, 3, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  staticTextFilterSizeUnit = new wxStaticText( itemPanel52, wxID_STATIC, _("MB"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStaticBoxSizer71->Add(staticTextFilterSizeUnit, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  notebookTools->AddPage(itemPanel52, _("Filter"));

  wxPanel* itemPanel75 = new wxPanel( notebookTools, ID_PANEL_SOFTWARE_COUNTERS, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  wxBoxSizer* itemBoxSizer76 = new wxBoxSizer(wxVERTICAL);
  itemPanel75->SetSizer(itemBoxSizer76);

  wxStaticBox* itemStaticBoxSizer77Static = new wxStaticBox(itemPanel75, wxID_STATIC, _(" Region "));
  wxStaticBoxSizer* itemStaticBoxSizer77 = new wxStaticBoxSizer(itemStaticBoxSizer77Static, wxHORIZONTAL);
  itemBoxSizer76->Add(itemStaticBoxSizer77, 0, wxGROW|wxALL, 5);
  wxBoxSizer* itemBoxSizer78 = new wxBoxSizer(wxVERTICAL);
  itemStaticBoxSizer77->Add(itemBoxSizer78, 0, wxGROW|wxALL, 5);
  radioSCOnIntervals = new wxRadioButton( itemPanel75, ID_RADIOBUTTON_SC_ON_INTERVALS, _("On intervals"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
  radioSCOnIntervals->SetValue(false);
  itemBoxSizer78->Add(radioSCOnIntervals, 1, wxGROW|wxALL, 5);

  radioSCOnStates = new wxRadioButton( itemPanel75, ID_RADIOBUTTON_SC_ON_STATES, _("On states"), wxDefaultPosition, wxDefaultSize, 0 );
  radioSCOnStates->SetValue(false);
  itemBoxSizer78->Add(radioSCOnStates, 1, wxGROW|wxALL, 5);

  wxStaticLine* itemStaticLine81 = new wxStaticLine( itemPanel75, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
  itemStaticBoxSizer77->Add(itemStaticLine81, 0, wxGROW|wxALL, 5);

  wxBoxSizer* itemBoxSizer82 = new wxBoxSizer(wxVERTICAL);
  itemStaticBoxSizer77->Add(itemBoxSizer82, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
  wxBoxSizer* itemBoxSizer83 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer82->Add(itemBoxSizer83, 1, wxGROW|wxALL, 5);
  staticTextSCSamplingInterval = new wxStaticText( itemPanel75, wxID_STATIC, _("Sampling Interval (ns)"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer83->Add(staticTextSCSamplingInterval, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  textSCSamplingInterval = new wxTextCtrl( itemPanel75, ID_TEXTCTRL_SC_SAMPLING_INTERVAL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer83->Add(textSCSamplingInterval, 2, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxBoxSizer* itemBoxSizer86 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer82->Add(itemBoxSizer86, 1, wxGROW|wxALL, 5);
  staticTextSCMinimumBurstTime = new wxStaticText( itemPanel75, wxID_STATIC, _("Min Burst Time (ns)"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer86->Add(staticTextSCMinimumBurstTime, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  textSCMinimumBurstTime = new wxTextCtrl( itemPanel75, ID_TEXTCTRL_SC_MINIMUM_BURST_TIME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer86->Add(textSCMinimumBurstTime, 2, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxStaticBox* itemStaticBoxSizer89Static = new wxStaticBox(itemPanel75, wxID_STATIC, _(" Selected events "));
  wxStaticBoxSizer* itemStaticBoxSizer89 = new wxStaticBoxSizer(itemStaticBoxSizer89Static, wxHORIZONTAL);
  itemBoxSizer76->Add(itemStaticBoxSizer89, 1, wxGROW|wxALL, 5);
  wxBoxSizer* itemBoxSizer90 = new wxBoxSizer(wxHORIZONTAL);
  itemStaticBoxSizer89->Add(itemBoxSizer90, 1, wxGROW|wxALL, 5);
  wxArrayString checkListSCSelectedEventsStrings;
  checkListSCSelectedEventsStrings.Add(_("42000059"));
  checkListSCSelectedEventsStrings.Add(_("42000008"));
  checkListSCSelectedEvents = new wxListBox( itemPanel75, ID_CHECKLISTBOX_SC_SELECTED_EVENTS, wxDefaultPosition, wxDefaultSize, checkListSCSelectedEventsStrings, wxLB_SINGLE );
  itemBoxSizer90->Add(checkListSCSelectedEvents, 2, wxGROW|wxALL, 5);

  wxBoxSizer* itemBoxSizer92 = new wxBoxSizer(wxVERTICAL);
  itemBoxSizer90->Add(itemBoxSizer92, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
  buttonSCSelectedEventsAdd = new wxButton( itemPanel75, ID_BUTTON_SC_SELECTED_EVENTS_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer92->Add(buttonSCSelectedEventsAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT|wxTOP, 5);

  buttonSCSelectedEventsDelete = new wxButton( itemPanel75, ID_BUTTON_SC_SELECTED_EVENTS_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer92->Add(buttonSCSelectedEventsDelete, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT|wxTOP, 5);

  wxStaticBox* itemStaticBoxSizer95Static = new wxStaticBox(itemPanel75, wxID_STATIC, _(" Options "));
  wxStaticBoxSizer* itemStaticBoxSizer95 = new wxStaticBoxSizer(itemStaticBoxSizer95Static, wxHORIZONTAL);
  itemBoxSizer76->Add(itemStaticBoxSizer95, 0, wxGROW|wxALL, 5);
  wxBoxSizer* itemBoxSizer96 = new wxBoxSizer(wxHORIZONTAL);
  itemStaticBoxSizer95->Add(itemBoxSizer96, 1, wxGROW|wxALL, 5);
  wxBoxSizer* itemBoxSizer97 = new wxBoxSizer(wxVERTICAL);
  itemBoxSizer96->Add(itemBoxSizer97, 1, wxGROW|wxALL, 5);
  radioSCCountEvents = new wxRadioButton( itemPanel75, ID_RADIOBUTTON_SC_COUNT_EVENTS, _("Count events"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
  radioSCCountEvents->SetValue(false);
  itemBoxSizer97->Add(radioSCCountEvents, 1, wxGROW|wxALL, 5);

  radioSCAccumulateValues = new wxRadioButton( itemPanel75, ID_RADIOBUTTON8, _("Accumulate values"), wxDefaultPosition, wxDefaultSize, 0 );
  radioSCAccumulateValues->SetValue(false);
  itemBoxSizer97->Add(radioSCAccumulateValues, 1, wxGROW|wxALL, 5);

  wxStaticLine* itemStaticLine100 = new wxStaticLine( itemPanel75, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
  itemBoxSizer96->Add(itemStaticLine100, 0, wxGROW|wxALL, 5);

  wxBoxSizer* itemBoxSizer101 = new wxBoxSizer(wxVERTICAL);
  itemBoxSizer96->Add(itemBoxSizer101, 1, wxGROW|wxALL, 5);
  checkSCRemoveStates = new wxCheckBox( itemPanel75, ID_CHECKBOX_SC_REMOVE_STATES, _("Remove states"), wxDefaultPosition, wxDefaultSize, 0 );
  checkSCRemoveStates->SetValue(false);
  itemBoxSizer101->Add(checkSCRemoveStates, 1, wxGROW|wxALL, 5);

  checkSCSummarizeUseful = new wxCheckBox( itemPanel75, ID_CHECKBOX_SC_SUMMARIZE_USEFUL, _("Summarize useful"), wxDefaultPosition, wxDefaultSize, 0 );
  checkSCSummarizeUseful->SetValue(false);
  itemBoxSizer101->Add(checkSCSummarizeUseful, 1, wxGROW|wxALL, 5);

  checkSCGlobalCounters = new wxCheckBox( itemPanel75, ID_CHECKBOX_SC_GLOBAL_COUNTERS, _("Global counters"), wxDefaultPosition, wxDefaultSize, 0 );
  checkSCGlobalCounters->SetValue(false);
  itemBoxSizer101->Add(checkSCGlobalCounters, 1, wxGROW|wxALL, 5);

  checkSCOnlyInBurstsCounting = new wxCheckBox( itemPanel75, ID_CHECKBOX_SC_ONLY_IN_BURSTS_COUNTING, _("Only in bursts counting"), wxDefaultPosition, wxDefaultSize, 0 );
  checkSCOnlyInBurstsCounting->SetValue(false);
  itemBoxSizer101->Add(checkSCOnlyInBurstsCounting, 1, wxGROW|wxALL, 5);

  wxStaticBox* itemStaticBoxSizer106Static = new wxStaticBox(itemPanel75, wxID_STATIC, _(" Keep events "));
  wxStaticBoxSizer* itemStaticBoxSizer106 = new wxStaticBoxSizer(itemStaticBoxSizer106Static, wxHORIZONTAL);
  itemBoxSizer76->Add(itemStaticBoxSizer106, 1, wxGROW|wxALL, 5);
  wxArrayString listSCKeepEventsStrings;
  listSCKeepEventsStrings.Add(_("40000003"));
  listSCKeepEvents = new wxListBox( itemPanel75, ID_LISTBOX_SC_KEEP_EVENTS, wxDefaultPosition, wxDefaultSize, listSCKeepEventsStrings, wxLB_SINGLE );
  itemStaticBoxSizer106->Add(listSCKeepEvents, 2, wxGROW|wxALL, 5);

  wxBoxSizer* itemBoxSizer108 = new wxBoxSizer(wxVERTICAL);
  itemStaticBoxSizer106->Add(itemBoxSizer108, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
  buttonSCKeepEventsAdd = new wxButton( itemPanel75, ID_BUTTON_SC_KEEP_EVENTS_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer108->Add(buttonSCKeepEventsAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

  buttonSCKeepEventsDelete = new wxButton( itemPanel75, ID_BUTTON_SC_KEEP_EVENTS_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer108->Add(buttonSCKeepEventsDelete, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

  notebookTools->AddPage(itemPanel75, _("Software Counters"));

  itemBoxSizer2->Add(notebookTools, 4, wxGROW|wxALL, 5);

  wxStdDialogButtonSizer* itemStdDialogButtonSizer111 = new wxStdDialogButtonSizer;

  itemBoxSizer2->Add(itemStdDialogButtonSizer111, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
  wxButton* itemButton112 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer111->AddButton(itemButton112);

  wxButton* itemButton113 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer111->AddButton(itemButton113);

  itemStdDialogButtonSizer111->Realize();

////@end CutFilterDialog content construction

  // Other initializations

  // Fill vector with tool names; sort here as you want them to appear in the tools list widget.
  listToolOrder.push_back( string("Cutter") );
  listToolOrder.push_back( string("Filter") );
  listToolOrder.push_back( string("Software Counters") );

  UpdateToolList();

  filePickerTrace->SetName( _( "Load Trace" ) );
  //filePickerTrace->SetPath( wxString::FromAscii( paraverConfig->getGlobalTracesPath().c_str() ) );

  // Allow only numeric character for text boxes.
  textCutterBeginCut->SetValidator( wxTextValidator( wxFILTER_NUMERIC ));
  textCutterEndCut->SetValidator( wxTextValidator( wxFILTER_NUMERIC ));
  textCutterTasks->SetValidator( wxTextValidator( wxFILTER_NUMERIC ));
  textSCSamplingInterval->SetValidator( wxTextValidator( wxFILTER_NUMERIC ));
  textSCMinimumBurstTime->SetValidator( wxTextValidator( wxFILTER_NUMERIC ));
}


/*!
 * Should we show tooltips?
 */

bool CutFilterDialog::ShowToolTips()
{
  return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CutFilterDialog::GetBitmapResource( const wxString& name )
{
  // Bitmap retrieval
////@begin CutFilterDialog bitmap retrieval
  wxUnusedVar(name);
  if (name == _T("arrow_up.xpm"))
  {
    wxBitmap bitmap(arrow_up_xpm);
    return bitmap;
  }
  else if (name == _T("arrow_down.xpm"))
  {
    wxBitmap bitmap(arrow_down_xpm);
    return bitmap;
  }
  return wxNullBitmap;
////@end CutFilterDialog bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CutFilterDialog::GetIconResource( const wxString& name )
{
  // Icon retrieval
////@begin CutFilterDialog icon retrieval
  wxUnusedVar(name);
  return wxNullIcon;
////@end CutFilterDialog icon retrieval
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX_CHECK_ORIGINAL_TIME
 */

void CutFilterDialog::OnCheckOriginalTimeClick( wxCommandEvent& event )
{
  if ( checkCutterUseOriginalTime->IsChecked() )
  {
    checkCutterBreakStates->SetValue( false );
    checkCutterBreakStates->Disable();
  }
  else
  {
    checkCutterBreakStates->Enable();
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON_PUSH_UP
 */

void CutFilterDialog::OnBitmapbuttonPushUpClick( wxCommandEvent& event )
{
  int lastItemSelected = checkListToolOrder->GetSelection();

  if ( lastItemSelected != wxNOT_FOUND && lastItemSelected > 0 )
  {
    // Save current check state, because UpdateToolList clears it
    vector< bool > checked;
    for( unsigned int i = 0; i < listToolOrder.size(); ++i )
      checked.push_back( checkListToolOrder->IsChecked( i ) );

    // Get check state of items to swap
    bool auxFirst  = checkListToolOrder->IsChecked( lastItemSelected - 1 );
    bool auxSecond = checkListToolOrder->IsChecked( lastItemSelected );

    // Swap the names in the string
    string auxNameFirst = listToolOrder[ lastItemSelected - 1 ];
    listToolOrder[ lastItemSelected - 1 ] =  listToolOrder[ lastItemSelected ];
    listToolOrder[ lastItemSelected ] = auxNameFirst;

    // Rebuild list
    UpdateToolList();

    // Recover and change check state
    for( unsigned int i = 0; i < listToolOrder.size(); ++i )
      checkListToolOrder->Check( i, checked[ i ] );

    checkListToolOrder->Check( lastItemSelected - 1, auxSecond );
    checkListToolOrder->Check( lastItemSelected, auxFirst );

    // Keep the selection
    checkListToolOrder->SetSelection( --lastItemSelected );
  }
}


void CutFilterDialog::UpdateToolList()
{
  wxArrayString items;
  int order = 1;
  for( vector< string >::iterator it = listToolOrder.begin(); it != listToolOrder.end(); ++it )
  {
    stringstream aux;
    aux << order++;
    items.Add(  wxString::FromAscii( aux.str().c_str() ) + _( ".- " ) + wxString::FromAscii( (*it).c_str() ) );
  }

  checkListToolOrder->Clear();
  checkListToolOrder->InsertItems( items, 0 );
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BITMAPBUTTON_PUSH_DOWN
 */

void CutFilterDialog::OnBitmapbuttonPushDownClick( wxCommandEvent& event )
{
  int lastItemSelected = checkListToolOrder->GetSelection();

  if ( lastItemSelected != wxNOT_FOUND && lastItemSelected < 2 )
  {
    // Save current check state, because UpdateToolList clears it
    vector< bool > checked;
    for( unsigned int i = 0; i < listToolOrder.size(); ++i )
      checked.push_back( checkListToolOrder->IsChecked( i ) );

    // Get check state of items to swap
    bool auxFirst  = checkListToolOrder->IsChecked( lastItemSelected );
    bool auxSecond = checkListToolOrder->IsChecked( lastItemSelected + 1 );

    // Swap the names in the string
    string auxNameFirst = listToolOrder[ lastItemSelected ];
    listToolOrder[ lastItemSelected ] =  listToolOrder[ lastItemSelected + 1 ];
    listToolOrder[ lastItemSelected + 1 ] = auxNameFirst;

    // Rebuild list
    UpdateToolList();

    // Recover and change check state
    for( unsigned int i = 0; i < listToolOrder.size(); ++i )
      checkListToolOrder->Check( i, checked[ i ] );

    checkListToolOrder->Check( lastItemSelected, auxSecond );
    checkListToolOrder->Check( lastItemSelected + 1, auxFirst );

    // Keep the selection
    checkListToolOrder->SetSelection( ++lastItemSelected );
  }
}


/*!
 * wxEVT_UPDATE_UI event handler for ID_CHECKLISTBOX
 */

void CutFilterDialog::OnCheckListToolOrderUpdate( wxUpdateUIEvent& event )
{
  int pos = 0;

  for( vector< string >::iterator it = listToolOrder.begin(); it != listToolOrder.end(); ++it )
  {
    for( size_t i = 0; i < notebookTools->GetPageCount(); ++i )
    {
      if ( *it == string( notebookTools->GetPageText( i ).c_str()))
      {
        (notebookTools->GetPage( i ))->Enable( checkListToolOrder->IsChecked( pos ) );
      }
    }

    pos++;
  }
}


/*!
 * wxEVT_FILEPICKER_CHANGED event handler for ID_FILECTRL_CUTFILTER_TRACE_SELECTION
 */

void CutFilterDialog::OnFilectrlTracePickerChanged( wxFileDirPickerEvent& event )
{
  wxString path = filePickerTrace->GetPath();
//  tracePath = wxFileName( path ).GetPath();
//  DoLoadTrace( std::string( path.mb_str() ) );
}

// This code is cut/paste from Histogram!!!!
wxString CutFilterDialog::formatNumber( double value )
{
  stringstream auxSStr;
  wxString auxNumber;

  locale mylocale( "" );
  auxSStr.imbue( mylocale );
  auxSStr.precision( ParaverConfig::getInstance()->getHistogramPrecision() );
  auxSStr << fixed;
  auxSStr << value;
  auxNumber << wxString::FromAscii( auxSStr.str().c_str() );

  return auxNumber;
}



/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_ALL_TRACE
 */

void CutFilterDialog::OnButtonCutterAllTraceClick( wxCommandEvent& event )
{
  radioCutterCutByTimePercent->SetValue( true );
  textCutterBeginCut->SetValue( formatNumber( 0 ));
  textCutterEndCut->SetValue( formatNumber( 100 ));
}


/*!
 * wxEVT_UPDATE_UI event handler for ID_PANEL_SOFTWARE_COUNTERS
 */

void CutFilterDialog::OnPanelSoftwareCountersUpdate( wxUpdateUIEvent& event )
{
  staticTextSCSamplingInterval->Enable( radioSCOnIntervals->GetValue() );
  textSCSamplingInterval->Enable( radioSCOnIntervals->GetValue() );

  staticTextSCMinimumBurstTime->Enable( !radioSCOnIntervals->GetValue() );
  textSCMinimumBurstTime->Enable( !radioSCOnIntervals->GetValue() );

  checkSCRemoveStates->Enable( radioSCOnIntervals->GetValue() );
  checkSCRemoveStates->SetValue( radioSCOnIntervals->GetValue() && checkSCRemoveStates->IsChecked() );

  checkSCSummarizeUseful->Enable( radioSCOnIntervals->GetValue() );
  checkSCSummarizeUseful->SetValue( radioSCOnIntervals->GetValue() && checkSCSummarizeUseful->IsChecked() );

  checkSCGlobalCounters->Enable( !radioSCAccumulateValues->GetValue() );
  checkSCGlobalCounters->SetValue( !radioSCAccumulateValues->GetValue() && checkSCGlobalCounters->IsChecked() );

  checkSCOnlyInBurstsCounting->Enable( radioSCOnIntervals->GetValue() );
  checkSCOnlyInBurstsCounting->SetValue( radioSCOnIntervals->GetValue() && checkSCOnlyInBurstsCounting->IsChecked() );
}


/*!
 * wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_CHECKLISTBOX
 */

void CutFilterDialog::OnCheckListToolOrderSelected( wxCommandEvent& event )
{
  int lastItemSelected = checkListToolOrder->GetSelection();

  if ( lastItemSelected != wxNOT_FOUND )
  {
    for( size_t i = 0; i < notebookTools->GetPageCount(); ++i )
    {
      if ( listToolOrder[ lastItemSelected ] == string( notebookTools->GetPageText( i ).c_str()))
        notebookTools->ChangeSelection( i );
    }
  }
}


/*!
 * wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK_CUT_FILTER_OPTIONS
 */

void CutFilterDialog::OnNotebookCutFilterOptionsPageChanged( wxNotebookEvent& event )
{
  int pos = 0;

  for( vector< string >::iterator it = listToolOrder.begin(); it != listToolOrder.end(); ++it )
  {
    if ( *it == string( notebookTools->GetPageText( notebookTools->GetSelection() ).c_str()) )
    {
      checkListToolOrder->SetSelection( pos );
    }
    pos++;
  }
}

void CutFilterDialog::TransferWindowToCutterData( bool previousWarning )
{
  if ( !previousWarning )
  {
    if ( traceOptions != NULL )
      traceOptions = new TraceOptions();

/*
        traceOptions->set_max_trace_size( int traceSize );
        traceOptions->set_by_time( bool whichByTime );
        traceOptions->set_min_cutting_time( unsigned long long minCutTime );
        traceOptions->set_max_cutting_time( unsigned long long maxCutTime );
        traceOptions->set_minimum_time_percentage( unsigned long long whichMinimumTimePercentage );
        traceOptions->set_maximum_time_percentage( unsigned long long whichMaximumTimePercentage );
        traceOptions->set_tasks_list( char *tasksList );
        traceOptions->set_original_time( char originalTime );
        traceOptions->set_break_states( int breakStates );
        traceOptions->set_remFirstStates( int remStates );
        traceOptions->set_remLastStates( int remStates );
*/
  }
}

void CutFilterDialog::TransferWindowToFilterData( bool previousWarning )
{
  if ( !previousWarning )
  {
    if ( traceOptions != NULL )
      traceOptions = new TraceOptions();
  }
}

void CutFilterDialog::TransferWindowToSoftwareCountersData( bool previousWarning )
{
  if ( !previousWarning )
  {
    if ( traceOptions != NULL )
      traceOptions = new TraceOptions();
  }
}

void CutFilterDialog::CheckCommonOptions( bool &previousWarning )
{
  // Any trace selected?
  wxString path = filePickerTrace->GetPath();
  if ( !previousWarning && path == _("") )
  {
    wxMessageDialog message( this, _("Missing trace name.\nPlease choose one trace."), _( "Warning" ), wxOK );
    message.ShowModal();
    filePickerTrace->SetFocus();
    previousWarning = true;
  }

  // Any tool selected?
  bool someUtilitySelected = false;
  for (size_t i = 0; i < checkListToolOrder->GetCount(); ++i )
  {
    if ( checkListToolOrder->IsChecked( i ) )
    {
      someUtilitySelected = true;
      break;
    }
  }

  if ( !previousWarning && !someUtilitySelected )
  {
    wxMessageDialog message( this, _("No utility selected.\nPlease choose the utilities to apply."), _( "Warning" ), wxOK );
    message.ShowModal();
    checkListToolOrder->SetFocus();
    previousWarning = true;
  }
}


void CutFilterDialog::CheckCutterOptions( bool &previousWarning )
{
  // Time region selected?
  if ( !previousWarning && textCutterBeginCut->GetValue() == "" )
  {
    wxMessageDialog message( this, _("Please set the initial time."), _( "Warning" ), wxOK );
    message.ShowModal();
    textCutterBeginCut->SetFocus();
    previousWarning = true;
  }

  if ( !previousWarning && textCutterEndCut->GetValue() == "" )
  {
    wxMessageDialog message( this, _("Please set the final time."), _( "Warning" ), wxOK );
    message.ShowModal();
    textCutterEndCut->SetFocus();
    previousWarning = true;
  }

  // Are time set properly?
  double cutterBeginTime, cutterEndTime;
  textCutterBeginCut->GetValue().ToDouble( &cutterBeginTime );
  textCutterEndCut->GetValue().ToDouble( &cutterEndTime );

  // negative times?
  if ( !previousWarning && cutterBeginTime < 0.0 )
  {
    wxMessageDialog message( this, _("Times must be positive numbers.\n\nPlease set begin time properly."), _( "Warning" ), wxOK );
    message.ShowModal();
    textCutterBeginCut->SetFocus();
    previousWarning = true;
  }

  if ( !previousWarning && cutterEndTime < 0.0 )
  {
    wxMessageDialog message( this, _("Times must be positive numbers.\n\nPlease set end time properly."), _( "Warning" ), wxOK );
    message.ShowModal();
    textCutterEndCut->SetFocus();
    previousWarning = true;
  }

  // percent out of range?
  if ( !previousWarning && radioCutterCutByTimePercent->GetValue() && cutterBeginTime > 100.0 )
  {
    wxMessageDialog message( this, _("Begin time percent greater than 100 %.\n\nPlease set time percent properly."), _( "Warning" ), wxOK );
    message.ShowModal();
    radioCutterCutByTimePercent->SetFocus();
    previousWarning = true;
  }

  if ( !previousWarning && radioCutterCutByTimePercent->GetValue() && cutterEndTime > 100.0 )
  {
    wxMessageDialog message( this, _("End time percent greater than 100 %.\n\nPlease set time percent properly."), _( "Warning" ), wxOK );
    message.ShowModal();
    radioCutterCutByTimePercent->SetFocus();
    previousWarning = true;
  }

  // begin == end?
  if ( !previousWarning && cutterBeginTime == cutterEndTime )
  {
    wxMessageDialog message( this, _("Same time for both limits.\n\nPlease set time range properly."), _( "Warning" ), wxOK );
    message.ShowModal();
    textCutterBeginCut->SetFocus();
    previousWarning = true;
  }

  // begin > end?
  if ( !previousWarning && cutterBeginTime > cutterEndTime ) // Idea: Maybe it could swap times in text boxes.
  {
    wxMessageDialog message( this, _("Begin time greater than end time.\n\nPlease set time range properly."), _( "Warning" ), wxOK );
    message.ShowModal();
    textCutterBeginCut->SetFocus();
    previousWarning = true;
  }
}


void CutFilterDialog::CheckFilterOptions( bool &previousWarning )
{
}


void CutFilterDialog::CheckSoftwareCountersOptions( bool &previousWarning )
{
}


void CutFilterDialog::OnOkClick( wxCommandEvent& event )
{
  // To avoid annoying multiple warning windows at the same time, and also final filter creation
  bool previousWarning = false;

  CheckCommonOptions( previousWarning );

  if ( !previousWarning )
  {
    // Which tools are selected?
    for (size_t i = 0; i < checkListToolOrder->GetCount(); ++i )
    {
      if ( checkListToolOrder->IsChecked( i ) )
      {
        if ( listToolOrder[ i ] == "Cutter" )
        {
          CheckCutterOptions( previousWarning );
          TransferWindowToCutterData( previousWarning );
        }
        if ( listToolOrder[ i ] == "Filter" )
        {
          CheckFilterOptions( previousWarning );
          TransferWindowToFilterData( previousWarning );
        }
        if ( listToolOrder[ i ] == "Software Counter" )
        {
          CheckSoftwareCountersOptions( previousWarning );
          TransferWindowToSoftwareCountersData( previousWarning );
        }
      }
    }
  }
}


string CutFilterDialog::GetTraceFileName()
{
  wxString path = filePickerTrace->GetPath();
  return std::string( path.mb_str() );
}


vector< int > CutFilterDialog::GetToolsOrder()
{
  vector< int > filterToolOrder;

  for ( size_t i = 0; i < listToolOrder.size(); ++i )
  {
    if ( checkListToolOrder->IsChecked( i ) )
    {
      if ( listToolOrder[ i ] == "Cutter" )
        filterToolOrder.push_back( INC_CHOP_COUNTER );
      if ( listToolOrder[ i ] == "Filter" )
        filterToolOrder.push_back( INC_FILTER_COUNTER );
      if ( listToolOrder[ i ] == "Software Counters" )
        filterToolOrder.push_back( INC_SC_COUNTER );
    }
  }

  return filterToolOrder;
}


bool CutFilterDialog::LoadResultingTrace()
{
  return loadResultingTrace->IsChecked();
}


/*!
 * wxEVT_UPDATE_UI event handler for ID_PANEL_FILTER
 */

void CutFilterDialog::OnPanelFilterUpdate( wxUpdateUIEvent& event )
{
  staticBoxSizerFilterStates->Enable( !checkFilterDiscardStateRecords->IsChecked() );
  checkListFilterStates->Enable( !checkFilterDiscardStateRecords->IsChecked() );
  buttonFilterSelectAll->Enable( !checkFilterDiscardStateRecords->IsChecked() );
  buttonFilterUnselectAll->Enable( !checkFilterDiscardStateRecords->IsChecked() );
  buttonFilterSetMinimumTime->Enable( !checkFilterDiscardStateRecords->IsChecked() );
  checkFilterDiscardListedStates->Enable( !checkFilterDiscardStateRecords->IsChecked() );

  staticBoxSizerFilterEvents->Enable( !checkFilterDiscardEventRecords->IsChecked() );
  listboxFilterEvents->Enable( !checkFilterDiscardEventRecords->IsChecked() );
  buttonFilterAdd->Enable( !checkFilterDiscardEventRecords->IsChecked() );
  buttonFilterDelete->Enable( !checkFilterDiscardEventRecords->IsChecked() );
  checkFilterDiscardListedEvents->Enable( !checkFilterDiscardEventRecords->IsChecked() );

  staticBoxSizerFilterCommunications->Enable( !checkFilterDiscardCommunicationRecords->IsChecked() );
  staticTextFilterSize->Enable( !checkFilterDiscardCommunicationRecords->IsChecked() );
  textFilterSize->Enable( !checkFilterDiscardCommunicationRecords->IsChecked() );
  staticTextFilterSizeUnit->Enable( !checkFilterDiscardCommunicationRecords->IsChecked() );
}

