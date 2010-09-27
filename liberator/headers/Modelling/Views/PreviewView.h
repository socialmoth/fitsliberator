// The ESA/ESO/NASA FITS Liberator - http://code.google.com/p/fitsliberator
//
// Copyright (c) 2004-2010, ESA/ESO/NASA.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the names of the European Space Agency (ESA), the European 
//       Southern Observatory (ESO) and the National Aeronautics and Space 
//       Administration (NASA) nor the names of its contributors may be used to
//       endorse or promote products derived from this software without specific
//       prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL ESA/ESO/NASA BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// =============================================================================
//
// The ESA/ESO/NASA FITS Liberator uses NASA's CFITSIO library, libtiff, 
// TinyXML, Boost C++ Libraries, Object Access Library and Intel Threading 
// Building Blocks.
//
// =============================================================================
//
// Project Executive:
//   Lars Lindberg Christensen
//
// Technical Project Manager:
//   Lars Holm Nielsen
//
// Developers:
//   Kaspar Kirstein Nielsen & Teis Johansen
// 
// Technical, scientific support and testing: 
//   Robert Hurt
//   Davide De Martin
//
// =============================================================================
#ifndef __PreviewView_H__
#define __PreviewView_H__

#include "FitsLiberator.h"
#include "Observer.h"

#include "PreviewModel.h"
#include "ToolModel.h"
#include "GlobalSettingsModel.h"
#include "PlaneModel.h"
#include "ProgressModel.h"

#include "PreviewController.h"
#include "FlowController.h"

#include "TextUtils.h"

namespace FitsLiberator
{
	namespace Modelling
	{
		/**
		*	Implements the super class for the preview view
		*	Should be extended by any platform or GUI specific 
		*	implementation
		*/
		class PreviewView : public Observer
		{
		public:
			PreviewView(
                PreviewModel&, ToolModel&, GlobalSettingsModel&, PlaneModel&, ProgressModel&,
                PreviewController&, FlowController&);
			~PreviewView();
			
            Void Update( Models * m );
            static String formatZoomFactor(Double zoomFactor);
			String getZoomText() const;
		protected:
			virtual Void drawPreview() = 0;
			virtual Void updateZooms(String*, Int) = 0;
			virtual Void setZoomCombo(Int) = 0;
			virtual Void setCurrentTool( ToolTypeFunction ) = 0;
			
			/**
			 * Must be overridden in platform specific view.
			 *
			 * Called to update the enable/disable state of the
			 * plus/minus/zoomCombo controls when the preview
			 * is enabled/disabled.
			 */
			virtual Void updateZoomComboState( Bool ) = 0;
            /** Called when a long-running task has begun. */
            virtual void gotBusy() = 0;
            /** Called when a long-running task has completed. */
            virtual void gotDone() = 0;

			PreviewModel&			model;  	///> the model for this view
			PreviewController&		controller;	///> the controller for this view
			ToolModel&				toolModel;	///> tool model for notifications of tool changes.
			PlaneModel&				planeModel;
            ProgressModel&          progressModel;
			GlobalSettingsModel&	globalSettingsModel;	///> global settings model - need to determine which masks should be drawn.
			FlowController&			flowController;
		};
	}
}

#endif