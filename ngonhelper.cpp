#include "ngonhelper.h"

NGonHelper::NGonHelper() : _modelingLib(NULL), _currentMesh(NULL)
{
}

NGonHelper::~NGonHelper()
{
	Modeling::Free(_modelingLib);
}

Bool NGonHelper::Init(PolygonObject* mesh, ULONG ngonIndex)
{
	TESTPOLONGER(mesh, false);
	if (ngonIndex >= (ULONG) mesh->GetNgonCount())
		return false;

	if (!_modelingLib)
		_modelingLib = Modeling::Alloc();

	if (_currentMesh != mesh)
	{
		if (!_modelingLib->InitObject(mesh))
			return false;
		_currentMesh = mesh;
	}	

	return _modelingLib->GetNgon(mesh, mesh->GetPolygonCount() + ngonIndex, &_ngon);
}

ULONG NGonHelper::GetPointCount() const
{
	return _ngon.count;
}

const LONG* NGonHelper::GetPoints() const
{
	return _ngon.points;
}

ULONG NGonHelper::GetOutlinePointCount() const
{
	return _ngon.segments[0];
}

LONG* NGonHelper::GetOutlinePoints() const
{
	return _ngon.points;
};

ULONG NGonHelper::GetHoleCount() const
{
	return _ngon.segcount - 1;
}

ULONG NGonHelper::GetHolePointCount(ULONG index) const
{
	if (index >= GetHoleCount())
		return 0;

	return _ngon.segments[index + 1];
}

LONG* NGonHelper::GetHolePoints(ULONG index) const
{
	if (index >= GetHoleCount())
		return nullptr;

	ULONG offset = 0;
	for (ULONG i = 0; i <= index; i++)
		offset += _ngon.segments[i];

	return _ngon.points + offset;
}
