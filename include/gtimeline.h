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

#pragma once



/*!
 * Includes
 */
#include <boost/date_time/posix_time/posix_time.hpp>

#include <wx/progdlg.h>
#include "prvtypes.h"

#ifdef _MSC_VER
#include <hash_set>
#else
#include  <unordered_set>
#endif

#ifdef _MSC_VER
using namespace stdext;
#endif

using boost::posix_time::ptime;

////@begin includes
#include "wx/frame.h"
#include "wx/splitter.h"
#include "wx/notebook.h"
#include "wx/richtext/richtextctrl.h"
////@end includes
#include <wx/treebase.h>

#include "wx/checkbox.h"
#include "wx/choicdlg.h"
#include "wx/dcmemory.h"
#include "wx/scrolwin.h"
#include "wx/timer.h"
#include "wx/icon.h"
#include "wx/slider.h"

#include "paraverkerneltypes.h"
#include "recordlist.h"
#include "copypaste.h"
#include "windows_tree.h"

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxSplitterWindow;
class wxNotebook;
class wxRichTextCtrl;
class wxBoxSizer;
////@end forward declarations
class Timeline;
class ProgressController;


/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_GTIMELINE 10001
#define ID_SPLITTER_TIMELINE 10048
#define ID_SCROLLED_DRAW 10007
#define ID_NOTEBOOK_INFO 10042
#define ID_SCROLLED_WHATWHERE 10076
#define ID_CHECKBOX 10077
#define ID_CHECKBOX1 10079
#define ID_CHECKBOX2 10080
#define ID_CHECKBOX3 10083
#define ID_CHECKBOX4 10084
#define ID_CHECKBOX5 10004
#define ID_CHECKBOX6 10005
#define ID_RICHTEXTCTRL 10043
#define ID_SCROLLED_TIMING 10044
#define ID_TEXTCTRL_INITIALTIME 10045
#define wxID_STATIC_INITIALSEMANTIC 10288
#define ID_TEXTCTRL_INITIALSEMANTIC 10000
#define ID_TEXTCTRL_FINALTIME 10046
#define wxID_STATIC_FINALSEMANTIC 10289
#define ID_TEXTCTRL_FINALSEMANTIC 10002
#define ID_TEXTCTRL_DURATION 10047
#define wxID_STATIC_SLOPE 10290
#define ID_TEXTCTRL_SLOPE 10003
#define ID_SCROLLEDWINDOW 10008
#define ID_CHECKBOX_CUSTOM_PALETTE 10606
#define ID_BUTTON_CUSTOM_PALETTE_APPLY 10006
#define ID_SCROLLED_COLORS 10049
#define ID_PANEL 10009
#define wxID_STATIC_RED 10295
#define ID_SLIDER_RED 10010
#define ID_TEXT_RED 10015
#define wxID_STATIC_GREEN 10293
#define ID_SLIDER_GREEN 10011
#define ID_TEXT_GREEN 10014
#define wxID_STATIC_BLUE 10294
#define ID_SLIDER_BLUE 10012
#define ID_TEXT_BLUE 10013
#define SYMBOL_GTIMELINE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMAXIMIZE_BOX|wxCLOSE_BOX|wxFRAME_NO_TASKBAR|wxWANTS_CHARS|wxFULL_REPAINT_ON_RESIZE
#define SYMBOL_GTIMELINE_TITLE _("gTimeline")
#define SYMBOL_GTIMELINE_IDNAME ID_GTIMELINE
#define SYMBOL_GTIMELINE_SIZE wxSize(400, 300)
#define SYMBOL_GTIMELINE_POSITION wxDefaultPosition
////@end control identifiers

#define ID_TIMER_SIZE 40000
#define ID_TIMER_MOTION 40001
#define ID_TIMER_WHEEL 40002


enum class TWhatWhereLine
{
  RAW_LINE = 0,
  BEGIN_OBJECT_SECTION,
  END_OBJECT_SECTION,
  BEGIN_PREVNEXT_SECTION,
  END_PREVNEXT_SECTION,
  BEGIN_CURRENT_SECTION,
  END_CURRENT_SECTION,
  BEGIN_SEMANTIC_SECTION,
  SEMANTIC_LINE,
  END_SEMANTIC_SECTION,
  BEGIN_RECORDS_SECTION,
  MARK_LINE,
  EVENT_LINE,
  COMMUNICATION_LINE,
  END_RECORDS_SECTION
};


/*!
 * gTimeline class declaration
 */
class gTimeline: public wxFrame, public gWindow
{
  DECLARE_CLASS( gTimeline )
  DECLARE_EVENT_TABLE()

public:
  /// Constructors
  gTimeline();
  gTimeline( wxWindow* parent, wxWindowID id = SYMBOL_GTIMELINE_IDNAME, const wxString& caption = SYMBOL_GTIMELINE_TITLE, const wxPoint& pos = SYMBOL_GTIMELINE_POSITION, const wxSize& size = SYMBOL_GTIMELINE_SIZE, long style = SYMBOL_GTIMELINE_STYLE );

  bool Create( wxWindow* parent, wxWindowID id = SYMBOL_GTIMELINE_IDNAME, const wxString& caption = SYMBOL_GTIMELINE_TITLE, const wxPoint& pos = SYMBOL_GTIMELINE_POSITION, const wxSize& size = SYMBOL_GTIMELINE_SIZE, long style = SYMBOL_GTIMELINE_STYLE );

  /// Destructor
  ~gTimeline();

  /// Initialises member variables
  void Init();

  /// Creates the controls and sizers
  void CreateControls();

////@begin gTimeline event handler declarations

  /// wxEVT_CLOSE_WINDOW event handler for ID_GTIMELINE
  void OnCloseWindow( wxCloseEvent& event );

  /// wxEVT_IDLE event handler for ID_GTIMELINE
  void OnIdle( wxIdleEvent& event );

  /// wxEVT_RIGHT_DOWN event handler for ID_GTIMELINE
  void OnRightDown( wxMouseEvent& event );

  /// wxEVT_COMMAND_SPLITTER_DOUBLECLICKED event handler for ID_SPLITTER_TIMELINE
  void OnSplitterTimelineSashDClick( wxSplitterEvent& event );

  /// wxEVT_COMMAND_SPLITTER_UNSPLIT event handler for ID_SPLITTER_TIMELINE
  void OnSplitterTimelineSashUnsplit( wxSplitterEvent& event );

  /// wxEVT_SIZE event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowSize( wxSizeEvent& event );

  /// wxEVT_PAINT event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowPaint( wxPaintEvent& event );

  /// wxEVT_ERASE_BACKGROUND event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowEraseBackground( wxEraseEvent& event );

  /// wxEVT_LEFT_DOWN event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowLeftDown( wxMouseEvent& event );

  /// wxEVT_LEFT_UP event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowLeftUp( wxMouseEvent& event );

  /// wxEVT_LEFT_DCLICK event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowLeftDClick( wxMouseEvent& event );

  /// wxEVT_MIDDLE_UP event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowMiddleUp( wxMouseEvent& event );

  /// wxEVT_RIGHT_DOWN event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowRightDown( wxMouseEvent& event );

  /// wxEVT_MOTION event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowMotion( wxMouseEvent& event );

  /// wxEVT_MOUSEWHEEL event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowMouseWheel( wxMouseEvent& event );

  /// wxEVT_KEY_DOWN event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowKeyDown( wxKeyEvent& event );

  /// wxEVT_UPDATE_UI event handler for ID_SCROLLED_DRAW
  void OnScrolledWindowUpdate( wxUpdateUIEvent& event );

  /// wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING event handler for ID_NOTEBOOK_INFO
  void OnNotebookInfoPageChanging( wxNotebookEvent& event );

  /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX
  void OnCheckWhatWhere( wxCommandEvent& event );

  /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX4
  void OnCheckWhatWhereText( wxCommandEvent& event );

  /// wxEVT_UPDATE_UI event handler for ID_CHECKBOX5
  void OnCheckWWShowDateUpdate( wxUpdateUIEvent& event );

  /// wxEVT_UPDATE_UI event handler for wxID_STATIC_SLOPE
  void OnStaticSlopeUpdate( wxUpdateUIEvent& event );

  /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX_CUSTOM_PALETTE
  void OnCheckboxCustomPaletteClick( wxCommandEvent& event );

  /// wxEVT_UPDATE_UI event handler for ID_CHECKBOX_CUSTOM_PALETTE
  void OnCheckboxCustomPaletteUpdate( wxUpdateUIEvent& event );

  /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_CUSTOM_PALETTE_APPLY
  void OnButtonCustomPaletteApplyClick( wxCommandEvent& event );

  /// wxEVT_UPDATE_UI event handler for ID_BUTTON_CUSTOM_PALETTE_APPLY
  void OnButtonCustomPaletteApplyUpdate( wxUpdateUIEvent& event );

  /// wxEVT_UPDATE_UI event handler for ID_SCROLLED_COLORS
  void OnScrolledColorsUpdate( wxUpdateUIEvent& event );

  /// wxEVT_UPDATE_UI event handler for wxID_STATIC_RED
  void OnStaticSelectedColorUpdate( wxUpdateUIEvent& event );

  /// wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER_RED
  void OnSliderSelectedColorUpdated( wxCommandEvent& event );

  /// wxEVT_UPDATE_UI event handler for ID_SLIDER_RED
  void OnSliderSelectedColorUpdateUI( wxUpdateUIEvent& event );

  /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXT_RED
  void OnTextSelectedColorUpdated( wxCommandEvent& event );

  /// wxEVT_UPDATE_UI event handler for ID_TEXT_RED
  void OnTextSelectedColorUpdate( wxUpdateUIEvent& event );

////@end gTimeline event handler declarations

  void MousePanMotion();
  void MousePanLeftUp( wxMouseEvent& event );
  
  void OnBackgroundAsZeroCheckClick( wxCommandEvent& event );

////@begin gTimeline member function declarations

  wxColour GetBackgroundColour() const { return backgroundColour ; }
  void SetBackgroundColour(wxColour value) { backgroundColour = value ; }

  long GetBeginRow() const { return beginRow ; }
  void SetBeginRow(long value) { beginRow = value ; }

  wxBitmap GetBufferImage() const { return bufferImage ; }
  void SetBufferImage(wxBitmap value) { bufferImage = value ; }

  bool GetCanRedraw() const { return canRedraw ; }
  void SetCanRedraw(bool value) { canRedraw = value ; }

  wxBitmap GetCommImage() const { return commImage ; }
  void SetCommImage(wxBitmap value) { commImage = value ; }

  bool GetDrawCaution() const { return drawCaution ; }
  void SetDrawCaution(bool value) { drawCaution = value ; }

  bool GetDrawCautionNegatives() const { return drawCautionNegatives ; }
  void SetDrawCautionNegatives(bool value) { drawCautionNegatives = value ; }

  wxBitmap GetDrawImage() const { return drawImage ; }
  void SetDrawImage(wxBitmap value) { drawImage = value ; }

  long GetEndRow() const { return endRow ; }
  void SetEndRow(long value) { endRow = value ; }

  bool GetEscapePressed() const { return escapePressed ; }
  void SetEscapePressed(bool value) { escapePressed = value ; }

  wxBitmap GetEventImage() const { return eventImage ; }
  void SetEventImage(wxBitmap value) { eventImage = value ; }

  TRecordTime GetFindBeginTime() const { return findBeginTime ; }
  void SetFindBeginTime(TRecordTime value) { findBeginTime = value ; }

  TRecordTime GetFindEndTime() const { return findEndTime ; }
  void SetFindEndTime(TRecordTime value) { findEndTime = value ; }

  TObjectOrder GetFindFirstObject() const { return findFirstObject ; }
  void SetFindFirstObject(TObjectOrder value) { findFirstObject = value ; }

  TObjectOrder GetFindLastObject() const { return findLastObject ; }
  void SetFindLastObject(TObjectOrder value) { findLastObject = value ; }

  wxMouseEvent GetFirstMotionEvent() const { return firstMotionEvent ; }
  void SetFirstMotionEvent(wxMouseEvent value) { firstMotionEvent = value ; }

  bool GetFirstUnsplit() const { return firstUnsplit ; }
  void SetFirstUnsplit(bool value) { firstUnsplit = value ; }

  wxColour GetForegroundColour() const { return foregroundColour ; }
  void SetForegroundColour(wxColour value) { foregroundColour = value ; }

  int GetInfoZoneLastSize() const { return infoZoneLastSize ; }
  void SetInfoZoneLastSize(int value) { infoZoneLastSize = value ; }

  TRecordTime GetLastEventFoundTime() const { return lastEventFoundTime ; }
  void SetLastEventFoundTime(TRecordTime value) { lastEventFoundTime = value ; }

  TObjectOrder GetLastFoundObject() const { return lastFoundObject ; }
  void SetLastFoundObject(TObjectOrder value) { lastFoundObject = value ; }

  TRecordTime GetLastSemanticFoundTime() const { return lastSemanticFoundTime ; }
  void SetLastSemanticFoundTime(TRecordTime value) { lastSemanticFoundTime = value ; }

  wxColour GetLogicalColour() const { return logicalColour ; }
  void SetLogicalColour(wxColour value) { logicalColour = value ; }

  wxPen GetLogicalPen() const { return logicalPen ; }
  void SetLogicalPen(wxPen value) { logicalPen = value ; }

  wxMouseEvent GetMotionEvent() const { return motionEvent ; }
  void SetMotionEvent(wxMouseEvent value) { motionEvent = value ; }

  Timeline* GetMyWindow() const { return myWindow ; }
  void SetMyWindow(Timeline* value) { myWindow = value ; }

  PRV_INT32 GetObjectAxisPos() const { return objectAxisPos ; }
  void SetObjectAxisPos(PRV_INT32 value) { objectAxisPos = value ; }

  wxFont GetObjectFont() const { return objectFont ; }
  void SetObjectFont(wxFont value) { objectFont = value ; }

  int GetObjectHeight() const { return objectHeight ; }
  void SetObjectHeight(int value) { objectHeight = value ; }

  std::vector<PRV_INT32> GetObjectPosList() const { return objectPosList ; }
  void SetObjectPosList(std::vector<PRV_INT32> value) { objectPosList = value ; }

  wxColour GetPhysicalColour() const { return physicalColour ; }
  void SetPhysicalColour(wxColour value) { physicalColour = value ; }

  wxPen GetPhysicalPen() const { return physicalPen ; }
  void SetPhysicalPen(wxPen value) { physicalPen = value ; }

  bool GetRedoColors() const { return redoColorsPanel ; }
  void SetRedoColors(bool value) { redoColorsPanel = value ; }

  wxStopWatch * GetRedrawStopWatch() const { return redrawStopWatch ; }
  void SetRedrawStopWatch(wxStopWatch * value) { redrawStopWatch = value ; }

  std::map< rgb, std::set<TSemanticValue> > GetSemanticColorsToValue() const { return semanticColorsToValue ; }
  void SetSemanticColorsToValue(std::map< rgb, std::set<TSemanticValue> > value) { semanticColorsToValue = value ; }

  wxFont GetSemanticFont() const { return semanticFont ; }
  void SetSemanticFont(wxFont value) { semanticFont = value ; }

  std::map< int, std::set<TSemanticValue> >  GetSemanticPixelsToValue() const { return semanticPixelsToValue ; }
  void SetSemanticPixelsToValue(std::map< int, std::set<TSemanticValue> >  value) { semanticPixelsToValue = value ; }

  std::map< TSemanticValue, rgb > GetSemanticValuesToColor() const { return semanticValuesToColor ; }
  void SetSemanticValuesToColor(std::map< TSemanticValue, rgb > value) { semanticValuesToColor = value ; }

  bool GetSplitChanged() const { return splitChanged ; }
  void SetSplitChanged(bool value) { splitChanged = value ; }

  PRV_INT32 GetTimeAxisPos() const { return timeAxisPos ; }
  void SetTimeAxisPos(PRV_INT32 value) { timeAxisPos = value ; }

  wxFont GetTimeFont() const { return timeFont ; }
  void SetTimeFont(wxFont value) { timeFont = value ; }

  wxTimer * GetTimerMotion() const { return timerMotion ; }
  void SetTimerMotion(wxTimer * value) { timerMotion = value ; }

  wxTimer * GetTimerSize() const { return timerSize ; }
  void SetTimerSize(wxTimer * value) { timerSize = value ; }

  wxTimer * GetTimerWheel() const { return timerWheel ; }
  void SetTimerWheel(wxTimer * value) { timerWheel = value ; }

  bool GetTiming() const { return timing ; }
  void SetTiming(bool value) { timing = value ; }

  TObjectOrder GetWheelZoomBeginObject() const { return wheelZoomBeginObject ; }
  void SetWheelZoomBeginObject(TObjectOrder value) { wheelZoomBeginObject = value ; }

  TRecordTime GetWheelZoomBeginTime() const { return wheelZoomBeginTime ; }
  void SetWheelZoomBeginTime(TRecordTime value) { wheelZoomBeginTime = value ; }

  TObjectOrder GetWheelZoomEndObject() const { return wheelZoomEndObject ; }
  void SetWheelZoomEndObject(TObjectOrder value) { wheelZoomEndObject = value ; }

  TRecordTime GetWheelZoomEndTime() const { return wheelZoomEndTime ; }
  void SetWheelZoomEndTime(TRecordTime value) { wheelZoomEndTime = value ; }

  double GetWheelZoomFactor() const { return wheelZoomFactor ; }
  void SetWheelZoomFactor(double value) { wheelZoomFactor = value ; }

  long GetZoomBegin() const { return zoomBeginX ; }
  void SetZoomBegin(long value) { zoomBeginX = value ; }

  long GetZoomBeginY() const { return zoomBeginY ; }
  void SetZoomBeginY(long value) { zoomBeginY = value ; }

  long GetZoomEnd() const { return zoomEndX ; }
  void SetZoomEnd(long value) { zoomEndX = value ; }

  long GetZoomEndY() const { return zoomEndY ; }
  void SetZoomEndY(long value) { zoomEndY = value ; }

  bool GetZoomXY() const { return zoomXY ; }
  void SetZoomXY(bool value) { zoomXY = value ; }

  bool GetZooming() const { return zooming ; }
  void SetZooming(bool value) { zooming = value ; }

  /// Retrieves bitmap resources
  wxBitmap GetBitmapResource( const wxString& name );

  /// Retrieves icon resources
  wxIcon GetIconResource( const wxString& name );
////@end gTimeline member function declarations

  /// Should we show tooltips?
  static bool ShowToolTips();

#ifdef __WXMAC__
  void drawStackedImages( wxDC& dc );
#endif
  void redraw();
  bool drawAxis( wxDC& dc, std::vector<TObjectOrder>& selected );
  void drawZeroAxis( wxDC& dc, std::vector<TObjectOrder>& selected );
  
#ifdef _MSC_VER
  template<typename ValuesType>
  void drawRow( wxDC& dc,
                TObjectOrder firstRow,
                vector< ValuesType >& valuesToDraw,
                std::unordered_set< PRV_INT32 >& eventsToDraw,
                std::unordered_set< commCoord >& commsToDraw,
                wxMemoryDC& eventdc, wxMemoryDC& eventmaskdc,
                wxMemoryDC& commdc, wxMemoryDC& commmaskdc );
#else
  template<typename ValuesType>
  void drawRow( wxDC& dc,
                TObjectOrder firstRow,
                std::vector< ValuesType >& valuesToDraw,
                std::unordered_set< PRV_INT32 >& eventsToDraw,
                std::unordered_set< commCoord, hashCommCoord >& commsToDraw,
                wxMemoryDC& eventdc, wxMemoryDC& eventmaskdc,
                wxMemoryDC& commdc, wxMemoryDC& commmaskdc );
#endif

  template<typename ValuesType>
  void drawRowColor( wxDC& dc, ValuesType valueToDraw, wxCoord objectPos, wxCoord timePos, float magnify );

  template<typename ValuesType>
  void drawRowFunction( wxDC& dc, ValuesType valueToDraw, int& semanticLastPos, wxCoord objectPos, wxCoord timePos, float magnify );

  template<typename ValuesType>
  void drawRowPunctual( wxDC& dc, ValuesType& valuesToDrawList, wxCoord objectPos, wxCoord timePos, float magnify );

  template<typename ValuesType>
  void drawRowFusedLines( wxDC& dc, ValuesType valueToDraw, int& semanticLastPos, wxCoord& timeLastPos, TObjectOrder whichObject, wxCoord timePos, bool isLastValue );

  void drawRowEvents( wxDC& eventdc, wxDC& eventmaskdc, TObjectOrder rowPos, std::unordered_set< PRV_INT32 >& eventsToDraw );
#ifdef _MSC_VER
  void drawRowComms( wxDC& commdc, wxDC& commmaskdc, TObjectOrder rowPos, std::unordered_set< commCoord >& commsToDraw );
#else
  void drawRowComms( wxDC& commdc, wxDC& commmaskdc, TObjectOrder rowPos, std::unordered_set< commCoord, hashCommCoord >& commsToDraw );
#endif
  
  void drawCommunicationLines( bool draw );
  void drawEventFlags( bool draw );
  void drawFunctionLineColor();
  void drawFusedLinesColor();

  void OnPopUpRightDown( void );

  // Pop Up Menu Methods
  void OnPopUpCopy( wxCommandEvent& event );
  void OnPopUpPasteDefaultSpecial( wxCommandEvent& event );
  void OnPopUpPasteSpecial( wxCommandEvent& event );
  void OnPopUpPasteTime( wxCommandEvent& event );
  void OnPopUpPasteObjects( wxCommandEvent& event );
  void OnPopUpPasteSize( wxCommandEvent& event );
  void OnPopUpPasteDuration( wxCommandEvent& event );
  void OnPopUpPasteSemanticScale( wxCommandEvent& event );
  void OnPopUpPasteCustomPalette( wxCommandEvent& event );
  void OnPopUpPasteFilterAll( wxCommandEvent& event );
  void OnPopUpPasteFilterCommunications( wxCommandEvent& event );
  void OnPopUpPasteFilterEvents( wxCommandEvent& event );
  void OnPopUpClone( wxCommandEvent& event );
  void OnPopUpRename( wxCommandEvent& event );
  void OnPopUpFitTimeScale( wxCommandEvent& event );
  void OnPopUpFitSemanticScaleMin( wxCommandEvent& event );
  void OnPopUpFitSemanticScaleMax( wxCommandEvent& event );
  void OnPopUpFitSemanticScale( wxCommandEvent& event );
  void OnPopUpFitObjects( wxCommandEvent& event );
  void OnPopUpViewCommunicationLines( wxCommandEvent& event );
  void OnPopUpViewEventFlags( wxCommandEvent& event );
  void OnPopUpFunctionLineColor( wxCommandEvent& event );
  void OnPopUpFusedLinesColor( wxCommandEvent& event );
  void OnPopUpPunctualColor( wxCommandEvent& event );
  void OnPopUpPunctualColorWindow( wxCommandEvent& event );
  void OnPopUpCodeColor( wxCommandEvent& event );
  void OnPopUpGradientColor( wxCommandEvent& event );
  void OnPopUpNotNullGradientColor( wxCommandEvent& event );
  void OnPopUpAlternativeGradientColor( wxCommandEvent& event );
  void OnPopUpGradientFunction( wxCommandEvent& event );
  void OnPopUpSemanticScaleMinAtZero( wxCommandEvent& event );
  void OnPopUpUndoZoom( wxCommandEvent& event );
  void OnPopUpRedoZoom( wxCommandEvent& event );
  
  void OnPopUpDrawModeTimeLast( wxCommandEvent& event );
  void OnPopUpDrawModeTimeRandom( wxCommandEvent& event );
  void OnPopUpDrawModeTimeRandomNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeTimeMaximum( wxCommandEvent& event );
  void OnPopUpDrawModeTimeMinimumNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeTimeAbsoluteMaximum( wxCommandEvent& event );
  void OnPopUpDrawModeTimeAbsoluteMinimumNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeTimeAverage( wxCommandEvent& event );
  void OnPopUpDrawModeTimeAverageNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeTimeMode( wxCommandEvent& event );

  void OnPopUpDrawModeObjectsLast( wxCommandEvent& event );
  void OnPopUpDrawModeObjectsRandom( wxCommandEvent& event );
  void OnPopUpDrawModeObjectsRandomNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeObjectsMaximum( wxCommandEvent& event );
  void OnPopUpDrawModeObjectsMinimumNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeObjectsAbsoluteMaximum( wxCommandEvent& event );
  void OnPopUpDrawModeObjectsAbsoluteMinimumNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeObjectsAverage( wxCommandEvent& event );
  void OnPopUpDrawModeObjectsAverageNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeObjectsMode( wxCommandEvent& event );

  void OnPopUpDrawModeBothLast( wxCommandEvent& event );
  void OnPopUpDrawModeBothRandom( wxCommandEvent& event );
  void OnPopUpDrawModeBothRandomNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeBothMaximum( wxCommandEvent& event );
  void OnPopUpDrawModeBothMinimumNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeBothAbsoluteMaximum( wxCommandEvent& event );
  void OnPopUpDrawModeBothAbsoluteMinimumNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeBothAverage( wxCommandEvent& event );
  void OnPopUpDrawModeBothAverageNotZero( wxCommandEvent& event );
  void OnPopUpDrawModeBothMode( wxCommandEvent& event );

  void OnPopUpPixelSize( wxCommandEvent& event );

  void OnPopUpLabels( wxCommandEvent& event );

  void OnPopUpObjectAxis( wxCommandEvent& event );

  void OnPopUpRunApp( wxCommandEvent& event );

  void OnPopUpSynchronize( wxCommandEvent& event );
  void OnPopUpRemoveGroup( wxCommandEvent& event );
  void OnPopUpRemoveAllGroups( wxCommandEvent& event );

  void OnPopUpRowSelection( wxCommandEvent& event );

  void OnPopUpInfoPanel( wxCommandEvent& event );
  
  void OnPopUpSaveCFG( wxCommandEvent& event );
  void OnPopUpSaveImageDialog( wxCommandEvent& event );
  void OnPopUpSaveText( wxCommandEvent& event );

  void OnMenuGradientFunction( TGradientFunction function );

  void drawTimeMarks( std::vector< TRecordTime> times,
                      std::vector<TObjectOrder> &selectedObjects,
                      bool drawXCross = false,
                      bool allObjects = true,
                      TObjectOrder lastFoundObject = TObjectOrder(0) );
  void OnFindDialog();

  gTimeline *clone( Timeline *clonedWindow,
                    wxWindow *parent,
                    wxTreeItemId idRoot1,
                    wxTreeItemId idRoot2,
                    bool mustRedraw = true );

  void rightDownManager();

  void resizeDrawZone( int width, int height );
  
  bool IsSplit() const;
  void OnPopUpTiming( wxCommandEvent& event );
  void EnableTiming( bool state );
  void OnItemColorLeftUp( wxMouseEvent& event );

  void saveImage( wxString whichFileName = _( "" ), TImageFormat filterIndex =  TImageFormat::PNG );
  void saveImageLegend( wxString whichFileName = _( "" ),
                        TImageFormat filterIndex =  TImageFormat::PNG,
                        bool appendLegendSuffix = true );
  void saveImageDialog( wxString whichFileName = _( "" ) );

  void saveText();
  void saveCFG();

  void setEnableDestroyButton( bool value );

  static wxProgressDialog *dialogProgress;
  static int numberOfProgressDialogUsers;
  
  
//  void OnRightClick(wxMouseEvent& event);
////@begin gTimeline member variables
  wxSplitterWindow* splitter;
  wxScrolledWindow* drawZone;
  wxNotebook* infoZone;
  wxScrolledWindow* whatWherePanel;
  wxCheckBox* checkWWSemantic;
  wxCheckBox* checkWWEvents;
  wxCheckBox* checkWWCommunications;
  wxCheckBox* checkWWPreviousNext;
  wxCheckBox* checkWWText;
  wxCheckBox* checkWWShowDate;
  wxCheckBox* checkWWHex;
  wxRichTextCtrl* whatWhereText;
  wxScrolledWindow* timingZone;
  wxTextCtrl* initialTimeText;
  wxStaticText* initialSemanticLabel;
  wxTextCtrl* initialSemanticText;
  wxTextCtrl* finalTimeText;
  wxStaticText* finalSemanticLabel;
  wxTextCtrl* finalSemanticText;
  wxTextCtrl* durationText;
  wxStaticText* slopeLabel;
  wxTextCtrl* slopeText;
  wxScrolledWindow* colorsPanelGlobal;
  wxCheckBox* checkboxCustomPalette;
  wxButton* buttonCustomPaletteApply;
  wxScrolledWindow* colorsPanel;
  wxBoxSizer* colorsSizer;
  wxBoxSizer* sizerSelectedColor;
  wxPanel* panelSelectedColor;
  wxStaticText* labelSelectedColorRed;
  wxSlider* sliderSelectedRed;
  wxTextCtrl* textSelectedRed;
  wxStaticText* labelSelectedColorGreen;
  wxSlider* sliderSelectedGreen;
  wxTextCtrl* textSelectedGreen;
  wxStaticText* labelSelectedColorBlue;
  wxSlider* sliderSelectedBlue;
  wxTextCtrl* textSelectedBlue;
  wxBitmap bufferImage;
  wxBitmap commImage;
  bool drawCaution;
  wxBitmap drawImage;
  wxBitmap eventImage;
  wxColour physicalColour;
private:
  wxColour backgroundColour;
  long beginRow;
  bool canRedraw;
  bool drawCautionNegatives;
  long endRow;
  bool escapePressed;
  TRecordTime findBeginTime;
  TRecordTime findEndTime;
  TObjectOrder findFirstObject;
  TObjectOrder findLastObject;
  wxMouseEvent firstMotionEvent;
  bool firstUnsplit;
  wxColour foregroundColour;
  int infoZoneLastSize;
  TRecordTime lastEventFoundTime;
  TObjectOrder lastFoundObject;
  TRecordTime lastSemanticFoundTime;
  wxColour logicalColour;
  wxPen logicalPen;
  wxMouseEvent motionEvent;
  Timeline* myWindow;
  PRV_INT32 objectAxisPos;
  wxFont objectFont;
  int objectHeight;
  std::vector<PRV_INT32> objectPosList;
  wxPen physicalPen;
  bool redoColorsPanel;
  wxStopWatch * redrawStopWatch;
  std::map< rgb, std::set<TSemanticValue> > semanticColorsToValue;
  wxFont semanticFont;
  std::map< int, std::set<TSemanticValue> >  semanticPixelsToValue; // // Used by function line drawings
  std::map< TSemanticValue, rgb > semanticValuesToColor; // Stored for SaveImage legend
  bool splitChanged;
  PRV_INT32 timeAxisPos;
  wxFont timeFont;
  wxTimer * timerMotion;
  wxTimer * timerSize;
  wxTimer * timerWheel;
  bool timing;
  TObjectOrder wheelZoomBeginObject;
  TRecordTime wheelZoomBeginTime;
  TObjectOrder wheelZoomEndObject;
  TRecordTime wheelZoomEndTime;
  double wheelZoomFactor;
  long zoomBeginX;
  long zoomBeginY;
  long zoomEndX;
  long zoomEndY;
  bool zoomXY;
  bool zooming;
////@end gTimeline member variables

  class CustomColorSemValue : public wxObject
  {
    public:
      enum class ColorType
      {
        BACKGROUND,
        AXIS,
        PUNCTUAL,
        SEMANTIC_VALUE
      };

      ColorType myColorType;
      TSemanticValue myValue;
      wxPanel *myPanel;
      wxStaticText *myText;
      wxFont originalFont;
  };

  // colorsPanel update info
  bool forceRedoColorsPanel;
  bool enableApplyButton;
  SemanticInfoType lastType;
  TSemanticValue lastMin;
  TSemanticValue lastMax;
  size_t lastValuesSize;
  bool codeColorSet;
  TGradientFunction gradientFunc;
  CustomColorSemValue* selectedCustomColor;
  wxStaticText *lastSelectedItemText = nullptr;
  wxFont originalUnselectectItemTextFont;
  wxPanel *backgroundColorPanel = nullptr;
  wxPanel *zeroColorPanel = nullptr;

  bool enabledAutoRedrawIcon;

#ifdef __WXMAC__
  wxBitmap zoomBMP;
#endif
#ifdef _WIN32
  bool wheelZoomObjects;
#endif

  wxWindow *parent;
  
  static const wxCoord drawBorder = 5;

  std::vector< std::pair< TWhatWhereLine, wxString > > whatWhereLines;
  int whatWhereSelectedTimeEventLines;
  int whatWhereSelectedTimeCommunicationLines;
  TRecordTime    whatWhereTime;
  TObjectOrder   whatWhereRow;
  TSemanticValue whatWhereSemantic;

  wxString formatTime( TRecordTime whichTime, bool showDate );
  void computeWhatWhere( TRecordTime whichTime,
                         TObjectOrder whichRow,
                         TSemanticValue whichSemantic,
                         bool textMode,
                         bool showDate,
                         bool hexMode );
  void printWhatWhere( );
  void printWWSemantic( TObjectOrder whichRow, bool clickedValue, bool textMode, bool hexMode );
  void printWWRecords( TObjectOrder whichRow, bool clickedValue, bool textMode, bool showDate );

  TSemanticValue getSemanticValueFromFusedLines( int whichY );
  bool getPixelFromFunctionLine( int whichX, int whichY, TObjectOrder whichObject, int& whichPixelPos );


  // Returns: window_name_with_spaces_underscored@traceName (without extension PRV)
  wxString buildFormattedFileName() const;

  void Unsplit();
  void Split();
  void OnTimerSize( wxTimerEvent& event );
  void OnTimerMotion( wxTimerEvent& event );
  void OnTimerWheel( wxTimerEvent& event );

  bool pixelToTimeObject( long x, long y, TTime& onTime, TObjectOrder& onObject );
  
  void doDrawCaution( wxDC& whichDC );
  
  // Called by saveLabelsImage
  void drawRectangle( wxMemoryDC& labelDC,
                       wxMemoryDC& scaleDC,
                       wxColour foregroundColour,
                       wxColour backgroundColour,
                       rgb semanticColour,
                       wxString semanticValueLabel,
                       int titleMargin,
                       int widthRect,
                       int heightRect,
                       bool tryHorizontal,
                       int& xdst,
                       int& ydst,
                       int xsrc,
                       int ysrc,
                       int imageWidth,
                       int imageHeight,
                       int imageStepY,
                       int imageStepXRectangle,
                       bool drawLabel );

  void setEnableDestroyParents( bool value );

  class ScaleImageVertical
  {
    public:
      ScaleImageVertical(
              Timeline* whichMyWindow,
              const std::map< TSemanticValue, rgb >& whichSemanticValues,
              wxColour whichBackground,
              wxColour whichForeground,
              int whichBackgroundMode, // wxSOLID or wxTRANSPARENT; wxTRANSPARENT overrides fore and back
              wxFont whichTextFont,
              wxString& whichImagePath,
              const wxString& whichImageInfix,
              wxBitmapType& whichImageType );

      virtual ~ScaleImageVertical();

      void process();
      void save();
      wxImage *getImage() { return scaleImage; }
      wxBitmap *getBitmap() { return scaleBitmap; }

    protected:
      virtual void init();
      virtual void sortSemanticValues();
      virtual void computeMaxLabelSize();
      virtual void computeImageSize();
      virtual void createDC();
      virtual void draw();
      virtual void bitmapToImage();
      virtual wxString buildScaleImagePath();
      virtual void drawLabeledRectangle( rgb semanticColour,
                                         wxString semanticValueLabel,
                                         bool drawIt = true );
      void destroyDC();

      Timeline *myWindow;
      std::map< TSemanticValue, rgb > semValues;
      wxColour background;
      wxColour foreground;
      int backgroundMode;
      wxFont textFont;
      wxString& imagePath;
      wxString imageInfix;
      wxBitmapType& imageType;
      TImageFormat filterIndex;
      wxString tmpSuffix;
      TSemanticValue currentMin;
      TSemanticValue currentMax;
      PRV_UINT32 precision;
      wxString extraPrefixOutlier;
      std::map< TSemanticValue, wxString > semanticValueLabel;
      TSemanticValue semanticValueWithLongestLabel;
      int titleMargin;
      int widthRect;
      int heightRect;
      int imageStepY;
      int imageStepXRectangle;
      bool drawOutliers;
      bool symbolicDesc;
      int imageWidth;
      int imageHeight;
      int xsrc;
      int ysrc;
      int xdst;
      int ydst;
      wxBitmap *scaleBitmap;
      wxMemoryDC *scaleDC;
      wxBitmap *scaleMaskBitmap;
      wxMemoryDC *scaleMaskDC;
      wxSize maxLabelSize;
      wxImage *scaleImage;
  };

  class ScaleImageVerticalCodeColor : public ScaleImageVertical
  {
    public:
      ScaleImageVerticalCodeColor(
              Timeline* whichMyWindow,
              const std::map< TSemanticValue, rgb >& whichSemanticValues,
              wxColour whichBackground,
              wxColour whichForeground,
              int whichBackgroundMode,
              wxFont whichTextFont,
              wxString& whichImagePath,
              const wxString& whichImageInfix,
              wxBitmapType& whichImageType );

      ~ScaleImageVerticalCodeColor()
      {}

    protected:
      virtual void init();
  };

  class ScaleImageVerticalGradientColor : public ScaleImageVertical
  {
    public:
      ScaleImageVerticalGradientColor(
              Timeline* whichMyWindow,
              const std::map< TSemanticValue, rgb >& whichSemanticValues,
              wxColour whichBackground,
              wxColour whichForeground,
              int whichBackgroundMode,
              wxFont whichTextFont,
              wxString& whichImagePath,
              const wxString& whichImageInfix,
              wxBitmapType& whichImageType );

      ~ScaleImageVerticalGradientColor()
      {}

    protected:
      int numSquaresWithoutOutliers;
      int totalSquares;

      virtual void init();
      virtual void sortSemanticValues();
      virtual void draw();
  };

  class ScaleImageVerticalFusedLines : public ScaleImageVertical
  {
    public:
      ScaleImageVerticalFusedLines(
              Timeline* whichMyWindow,
              const std::map< TSemanticValue, rgb >& whichSemanticValues,
              wxColour whichBackground,
              wxColour whichForeground,
              int whichBackgroundMode,
              wxFont whichTextFont,
              wxString& whichImagePath,
              const wxString& whichImageInfix,
              wxBitmapType& whichImageType );

      ~ScaleImageVerticalFusedLines()
      {}

    protected:
      virtual void init();
      virtual void computeMaxLabelSize();
  };


  class ScaleImageHorizontalGradientColor : public ScaleImageVerticalGradientColor
  {
    public:
      ScaleImageHorizontalGradientColor(
              Timeline* whichMyWindow,
              const std::map< TSemanticValue, rgb >& whichSemanticValues,
              wxColour whichBackground,
              wxColour whichForeground,
              int whichBackgroundMode,
              wxFont whichTextFont,
              wxString& whichImagePath,
              const wxString& whichImageInfix,
              wxBitmapType& whichImageType,
              int whichWantedWidth = 0 );


      ~ScaleImageHorizontalGradientColor()
      {}

    protected:
      virtual void init();
      virtual void computeImageSize();
      virtual void draw();

    private:
      typedef enum { LEFT = 0, CENTER, RIGHT } TAlign;
      typedef enum { FIRST = 0, MIDDLE, LAST, ANY } TPosition;

      int SIZE_OF_TINY_MARK;
      int outlierMargin; // Inner margin between outlier and whole scale
      int wantedWidth;

      void drawRectangle( rgb semanticColour, TPosition position = ANY );
      void drawLabel( wxString semanticValueLabel, bool drawIt = true, TAlign align = LEFT );
  };
};
