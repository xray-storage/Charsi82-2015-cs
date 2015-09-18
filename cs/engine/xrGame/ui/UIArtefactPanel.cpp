#include "StdAfx.h"
#include "UIArtefactPanel.h"
#include "UIInventoryUtilities.h"
#include "UIXmlInit.h"

#include "../artifact.h"

using namespace InventoryUtilities;

CUIArtefactPanel::CUIArtefactPanel()
{		
}

CUIArtefactPanel::~CUIArtefactPanel()
{
}

void CUIArtefactPanel::InitFromXML	(CUIXml& xml, LPCSTR path, int index)
{
	CUIXmlInit::InitWindow		(xml, path, index, this);
	m_cell_size.x				= xml.ReadAttribFlt(path, index, "cell_width");
	m_cell_size.y				= xml.ReadAttribFlt(path, index, "cell_height");
	m_fScale					= xml.ReadAttribFlt(path, index, "scale");
}

void CUIArtefactPanel::InitIcons(const xr_vector<const CArtefact*>& artefacts)
{
	m_si.SetShader(GetEquipmentIconsShader());
	m_vRects.clear();
	for(xr_vector<const CArtefact*>::const_iterator it = artefacts.begin();
		it != artefacts.end(); it++)
	{
		const CArtefact* artefact = *it;
		Frect rect;
		Irect item_grid_rect = artefact->GetInvGridRect();
		rect.x1 = float(item_grid_rect.x1*INV_GRID_WIDTH);
		rect.y1 = float(item_grid_rect.y1*INV_GRID_HEIGHT);
		rect.x2 = rect.x1 + float(item_grid_rect.x2*INV_GRID_WIDTH);
		rect.y2 = rect.y1 + float(item_grid_rect.y2*INV_GRID_HEIGHT);
		m_vRects.push_back(rect);
	}
}

void CUIArtefactPanel::Draw(){
	const float iIndent = 1.0f;
	      float x = 0.0f;
		  float y = 0.0f;
		  float iHeight;
		  float iWidth;

	Frect				rect;
	GetAbsoluteRect		(rect);
	x					= rect.left;
	y					= rect.top;	
	
	float _s			= m_cell_size.x/m_cell_size.y;

	for (ITr it = m_vRects.begin(); it != m_vRects.end(); ++it)
	{
		const Frect& r = *it;		

		iHeight = m_fScale*(r.bottom - r.top);
		iWidth  = _s*m_fScale*(r.right - r.left);

		m_si.SetOriginalRect(r.left, r.top, r.width(), r.height());
		m_si.SetRect(0, 0, iWidth, iHeight);

		m_si.SetPos(x, y);
		x = x + iIndent + iWidth;

        m_si.Render();
	}

	CUIWindow::Draw();
}