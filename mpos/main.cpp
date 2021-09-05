#include "Hazelnupp.h"
#include <iostream>

#define SetMpos_Version (0.5)

using namespace Hazelnp;
using Hazelnupp = CmdArgsInterface;
Hazelnupp nupp;

// Configure the command line interface, Hazelnupp
void ConfigureCli()
{
	// Brief description
	nupp.SetBriefDescription("A super simple command line tool to set the mouse position.");

	// x, y parameters
	nupp.RegisterDescription("--x", "The x coordinate to set the cursor to. If no information on x is supplied, the current position will be used.");
	nupp.RegisterDescription("--y", "The y coordinate to set the cursor to. If no information on y is supplied, the current position will be used.");

	nupp.RegisterConstraint("--x", ParamConstraint::TypeSafety(DATA_TYPE::INT, true).AddIncompatibilities("--delta-x"));
	nupp.RegisterConstraint("--y", ParamConstraint::TypeSafety(DATA_TYPE::INT, true).AddIncompatibilities("--delta-y"));

	nupp.RegisterAbbreviation("-x", "--x");
	nupp.RegisterAbbreviation("-y", "--y");

	// Delta position
	nupp.RegisterDescription("--delta-x", "Move the cursor by --delta-x pixels on the x axis. If no information on x is supplied, the current position will be used.");
	nupp.RegisterDescription("--delta-y", "Move the cursor by --delta-y pixels on the y axis. If no information on y is supplied, the current position will be used.");

	nupp.RegisterConstraint("--delta-x", ParamConstraint::TypeSafety(DATA_TYPE::INT, true).AddIncompatibilities("--x"));
	nupp.RegisterConstraint("--delta-y", ParamConstraint::TypeSafety(DATA_TYPE::INT, true).AddIncompatibilities("--y"));

	nupp.RegisterAbbreviation("-dx", "--delta-x");
	nupp.RegisterAbbreviation("-dy", "--delta-y");

	// DPI scaling
	nupp.RegisterDescription("--disable-dpi-scaling", "Don't make this process DPI aware. This may result in inaccurate cursor positions.");
	nupp.RegisterConstraint("--disable-dpi-scaling", ParamConstraint::TypeSafety(DATA_TYPE::VOID, true));
	nupp.RegisterAbbreviation("--no-dpi", "--disable-dpi-scaling");

	// Version
	nupp.RegisterDescription("--version", "Will just print the version and exits.");
	nupp.RegisterAbbreviation("-v", "--version");
	nupp.RegisterConstraint("--version", ParamConstraint::TypeSafety(DATA_TYPE::VOID, true));

	return;
}

#include <Windows.h>

int main(int argc, char** argv)
{	
	// Configure and load the command line interface arguments
	ConfigureCli();
	nupp.Parse(argc, argv);

	// Print version and exit, if asked for version
	if (nupp.HasParam("--version"))
	{
		std::cout << SetMpos_Version << std::endl;
		return 0;
	}


	// Set process DPI aware, if not specifically requested otherwise
	if (!nupp.HasParam("--disable-dpi-scaling"))
		SetProcessDPIAware();

	// Create cursor positions, and read in the existing coordinates
	POINT newCursorCoordinates;
	POINT currentCursorCoordinates; GetCursorPos(&currentCursorCoordinates);

	// Calculate new x position
	// User wants a delta position
	if (nupp.HasParam("--delta-x"))
		newCursorCoordinates.x = currentCursorCoordinates.x + nupp["--delta-x"].GetInt32();
	// User wants an absolute position
	else if (nupp.HasParam("--x"))
		newCursorCoordinates.x = nupp["--x"].GetInt32();
	// User doesn't want to change this position
	else
		newCursorCoordinates.x = currentCursorCoordinates.x;

	// Calculate new y position
	// User wants a delta position
	if (nupp.HasParam("--delta-y"))
		newCursorCoordinates.y = currentCursorCoordinates.y + nupp["--delta-y"].GetInt32();
	// User wants an absolute position
	else if (nupp.HasParam("--y"))
		newCursorCoordinates.y = nupp["--y"].GetInt32();
	// User doesn't want to change this position
	else
		newCursorCoordinates.y = currentCursorCoordinates.y;

	// Set new cursor position
	SetCursorPos(newCursorCoordinates.x, newCursorCoordinates.y);

	return 0;
}
