#ifndef NGONHELPER_H__
#define NGONHELPER_H__

#include "c4d.h"
#include "lib_modeling.h"
#include "lib_ngon.h"

// Helper class to access NGon data
// Encapsulates NGons implementation specifics (how arrays are built, segment concept)
//
// We are using the modeling lib to access the NGon information from the Ngon class.
// We encapsulate the segment concept by providing outline and hole methods.
//
// For info the segment indexed 0 hold the outline edges
// Any additional segment define holes (with a reverse winding).
// We don't deal with edges at the moment.
class NGonHelper
{
public:
	NGonHelper();
	~NGonHelper();

	// Initialize the helper object.  Must be called before using the object.
	// Can be re-initialized.
	Bool Init(PolygonObject* mesh, ULONG ngonIndex);

	// Return the number of points(vertices) affected to this NGon
	ULONG GetPointCount() const;

	// Return the point (vertex) pointer.
	// Call GetPointCount to get the array size.
	const LONG* GetPoints() const;

	// Return the number of points on the outline of this NGon
	ULONG GetOutlinePointCount() const;

	// Return the outline point (vertex) pointer.
	// Call GetOutlinePointCount to get the array size.
	LONG* GetOutlinePoints() const;

	// Return the number of holes found in this NGon.
	ULONG GetHoleCount() const;

	// Return the number of points defining a specific hole on this NGon
	// index is the hole index
	ULONG GetHolePointCount(ULONG index) const;

	// Return a specific hole point (vertex) pointer.
	// index is the hole index
	LONG* GetHolePoints(ULONG index) const;

private:
	Modeling* _modelingLib;
	Ngon			_ngon;
	PolygonObject* _currentMesh;
};
#endif	// NGONHELPER_H__
