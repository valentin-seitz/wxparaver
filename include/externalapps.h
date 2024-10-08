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

#include <wx/string.h>
#include <array>

enum class TExternalApp
{
  // --- Called through RunScript choice selector widget --- 
  DIMEMAS_WRAPPER = 0, // Dimemas
  PRVSTATS_WRAPPER,    // prvstats
  CLUSTERING,          // Clustering
  FOLDING,             // Folding
  PROFET,              // Profet
                        // <-- add new apps here at most
  USER_COMMAND,        // User command

  // --- Called by different widget ---
  DIMEMAS_GUI,         // DimemasGui   invoked through button

  NUMBER_APPS
};

class ExternalApps
{
  public:
    ExternalApps() = delete;

    static wxString getApplicationLabel( TExternalApp whichApp );
    static wxString getApplicationBin( TExternalApp whichApp );
    static wxString getApplicationCheckBin( TExternalApp whichApp );

  private:
    // Labels to construct selector & warning dialogs
    static const std::array< wxString, (int)TExternalApp::NUMBER_APPS > applicationLabel;

    // Application binary names
    static const std::array< wxString, (int)TExternalApp::NUMBER_APPS > applicationBin;

    // Application binary check names
    static const std::array< wxString, (int)TExternalApp::NUMBER_APPS > applicationCheckBin;

};
