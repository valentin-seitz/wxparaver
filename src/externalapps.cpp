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

#include <wx/arrstr.h>
#include <wx/utils.h> 

#include "externalapps.h"

// Labels to construct selector & warning dialogs
const std::array< wxString, (int)TExternalAppID::NUMBER_APPS > ExternalApps::applicationLabel = {
  wxString( "Dimemas" ),      //DIMEMAS
  wxString( "prvstats" ),     //PRVSTATS
  wxString( "Clustering" ),   //CLUSTERING
  wxString( "Folding" ),      //FOLDING
  wxString( "PROFET" ),       //PROFET
  wxString( "User command" ), //USER_COMMAND

  // Following only for warning dialogs
  wxString( "DimemasGUI" )    //DIMEMAS_GUI
};

// Application binary names
const std::array< wxString, (int)TExternalAppID::NUMBER_APPS > ExternalApps::applicationBin = {
  wxString( "dimemas-wrapper.sh"),  // DIMEMAS
#ifdef _WIN32
  wxString( "prvstats.exe"),        // PRVSTATS
#else
  wxString( "prvstats-wrapper.sh"), // PRVSTATS
#endif
  wxString( "BurstClustering"),     // CLUSTERING
  wxString( "rri-auto"),            // FOLDING
  wxString( "profet-prv"),          // PROFET
  wxString( "" ),                   // USER_COMMAND
  wxString( "DimemasGUI")           // DIMEMAS_GUI
};

// Application binary check names
const std::array< wxString, (int)TExternalAppID::NUMBER_APPS > ExternalApps::applicationCheckBin = {
  wxString( "Dimemas" ),         // DIMEMAS
  wxString( "prvstats" ),        // PRVSTATS
  wxString( "BurstClustering" ), // CLUSTERING
  wxString( "rri-auto" ),        // FOLDING
  wxString( "profet-prv" ),      // PROFET
  wxString( "" ),                // USER_COMMAND
  wxString( "DimemasGUI")        // DIMEMAS_GUI
};

wxString ExternalApps::getApplicationLabel( TExternalAppID whichApp )
{
  return ExternalApps::applicationLabel[ static_cast< int >( whichApp ) ];
}

wxString ExternalApps::getApplicationBin( TExternalAppID whichApp )
{
  return ExternalApps::applicationBin[ static_cast< int >( whichApp ) ];
}

wxString ExternalApps::getApplicationCheckBin( TExternalAppID whichApp )
{
  return ExternalApps::applicationCheckBin[ static_cast< int >( whichApp ) ];
}

bool ExternalApps::existCommand( const wxString& program )
{
  static wxArrayString tmpOutput, tmpErrors;
  return wxExecute( program + " --version", tmpOutput, tmpErrors, wxEXEC_SYNC ) == 0;
}

bool ExternalApps::existCommand( TExternalAppID programID )
{
  return ExternalApps::existCommand( getApplicationCheckBin( programID ) );
}
