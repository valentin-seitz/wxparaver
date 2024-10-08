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

#include "externalapps.h"

// Labels to construct selector & warning dialogs
const std::array< wxString, (int)TExternalApp::NUMBER_APPS > ExternalApps::applicationLabel = {
  wxString( "Dimemas" ),      //DIMEMAS_WRAPPER
  wxString( "prvstats" ),     //PRVSTATS_WRAPPER
  wxString( "Clustering" ),   //CLUSTERING
  wxString( "Folding" ),      //FOLDING
  wxString( "PROFET" ),       //PROFET
  wxString( "User command" ), //USER_COMMAND

  // Following only for warning dialogs
  wxString( "DimemasGUI" )    //DIMEMAS_GUI
};

// Application binary names
const std::array< wxString, (int)TExternalApp::NUMBER_APPS > ExternalApps::applicationBin = {
  wxString( "dimemas-wrapper.sh"),  // DIMEMAS_WRAPPER
#ifdef _WIN32
  wxString( "prvstats.exe"),        // PRVSTATS_WRAPPER
#else
  wxString( "prvstats-wrapper.sh"), // PRVSTATS_WRAPPER
#endif
  wxString( "BurstClustering"),     // CLUSTERING
  wxString( "rri-auto"),            // FOLDING
  wxString( "profet-prv"),          // PROFET
  wxString( "" ),                   // USER_COMMAND
  wxString( "DimemasGUI")           // DIMEMAS_GUI
};

// Application binary check names
const std::array< wxString, (int)TExternalApp::NUMBER_APPS > ExternalApps::applicationCheckBin = {
  wxString( "Dimemas" ),         // DIMEMAS_WRAPPER
  wxString( "prvstats" ),        // PRVSTATS_WRAPPER
  wxString( "BurstClustering" ), // CLUSTERING
  wxString( "rri-auto" ),        // FOLDING
  wxString( "profet-prv" ),      // PROFET
  wxString( "" ),                // USER_COMMAND
  wxString( "DimemasGUI")        // DIMEMAS_GUI
};

wxString ExternalApps::getApplicationLabel( TExternalApp whichApp )
{
  return ExternalApps::applicationLabel[ static_cast< int >( whichApp ) ];
}

wxString ExternalApps::getApplicationBin( TExternalApp whichApp )
{
  return ExternalApps::applicationBin[ static_cast< int >( whichApp ) ];
}

wxString ExternalApps::getApplicationCheckBin( TExternalApp whichApp )
{
  return ExternalApps::applicationCheckBin[ static_cast< int >( whichApp ) ];
}
