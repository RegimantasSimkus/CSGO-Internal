#pragma once

#include "Vector.h"

class CSteamAPIContext;
struct adsp_auto_params_t;
class ClientClass;
struct model_t;
class CSentence;
struct vrect_t;
struct cmodel_t;
class IMaterial;
class CAudioSource;
class CMeasureSection;
class SurfInfo;
class ISpatialQuery;
struct cache_user_t;
class IMaterialSystem;
class VMatrix;
struct ScreenFade_t;
struct ScreenShake_t;
class CViewSetup;
class CEngineSprite;
class CGlobalVarsBase;
class CPhysCollide;
class CSaveRestoreData;
class INetChannelInfo;
struct datamap_t;
struct typedescription_t;
class CStandardRecvProxies;
struct client_textmessage_t;
class IAchievementMgr;
class ISPSharedMemory;
class IDemoRecorder;
struct AudioState_t;
class CGamestatsData;
class KeyValues;
class IFileList;
class IReplayFactory;
struct WriteReplayScreenshotParams_t;
class IMaterialProxy;
struct InputEvent_t;
struct SpatializationInfo_t;
class IScaleformSlotInitController;
class IConVar;
class CJob;
class CSVCMsg_HltvReplay;
class INetMessage;
class CEngineGotvSyncPacket;





//
//
//
//
//
//struct matrix3x4_t
//{
//	matrix3x4_t() {}
//	matrix3x4_t(
//		float m00, float m01, float m02, float m03,
//		float m10, float m11, float m12, float m13,
//		float m20, float m21, float m22, float m23)
//	{
//		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
//		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
//		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
//	}
//
//	/// Creates a matrix where the X axis = forward the Y axis = left, and the Z axis = up
//	void InitXYZ(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin)
//	{
//		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
//		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
//		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
//	}
//
//	//-----------------------------------------------------------------------------
//	// Creates a matrix where the X axis = forward
//	// the Y axis = left, and the Z axis = up
//	//-----------------------------------------------------------------------------
//	void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin)
//	{
//		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
//		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
//		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
//	}
//
//	//-----------------------------------------------------------------------------
//	// Creates a matrix where the X axis = forward
//	// the Y axis = left, and the Z axis = up
//	//-----------------------------------------------------------------------------
//	matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin)
//	{
//		Init(xAxis, yAxis, zAxis, vecOrigin);
//	}
//
//	inline void InitFromQAngles(const QAngle& angles, const Vector& vPosition);
//	inline void InitFromQAngles(const QAngle& angles);
//	inline void InitFromRadianEuler(const RadianEuler& angles, const Vector& vPosition);
//	inline void InitFromRadianEuler(const RadianEuler& angles);
//	inline void InitFromCTransform(const CTransform& transform);
//	inline void InitFromQuaternion(const Quaternion& orientation, const Vector& vPosition);
//	inline void InitFromQuaternion(const Quaternion& orientation);
//	inline void InitFromDiagonal(const Vector& vDiagonal);
//
//	inline Quaternion ToQuaternion() const;
//	inline QAngle ToQAngle() const;
//	inline CTransform ToCTransform() const;
//
//	inline void SetToIdentity();
//
//	/// multiply the scale/rot part of the matrix by a constant. This doesn't init the matrix ,
//	/// just scale in place. So if you want to construct a scaling matrix, init to identity and
//	/// then call this.
//	FORCEINLINE void ScaleUpper3x3Matrix(float flScale);
//
//	/// modify the origin
//	inline void SetOrigin(Vector const& p)
//	{
//		m_flMatVal[0][3] = p.x;
//		m_flMatVal[1][3] = p.y;
//		m_flMatVal[2][3] = p.z;
//	}
//
//	/// return the origin
//	inline Vector GetOrigin(void) const
//	{
//		Vector vecRet(m_flMatVal[0][3], m_flMatVal[1][3], m_flMatVal[2][3]);
//		return vecRet;
//	}
//
//	bool operator==(const matrix3x4_t& other) const
//	{
//		return memcmp(this, &other, sizeof(matrix3x4_t)) == 0;
//	}
//
//	bool operator!=(const matrix3x4_t& other) const
//	{
//		return memcmp(this, &other, sizeof(matrix3x4_t)) != 0;
//	}
//
//	inline bool IsEqualTo(const matrix3x4_t& other, float flTolerance = 1e-5f) const;
//
//	inline void GetBasisVectorsFLU(Vector* pForward, Vector* pLeft, Vector* pUp) const;
//	inline Vector TransformVector(const Vector& v0) const;
//	inline Vector RotateVector(const Vector& v0) const;
//	inline Vector TransformVectorByInverse(const Vector& v0) const;
//	inline Vector RotateVectorByInverse(const Vector& v0) const;
//	inline Vector RotateExtents(const Vector& vBoxExtents) const; // these are extents and must remain positive/symmetric after rotation
//	inline void TransformAABB(const Vector& vecMinsIn, const Vector& vecMaxsIn, Vector& vecMinsOut, Vector& vecMaxsOut) const;
//	inline void TransformAABBByInverse(const Vector& vecMinsIn, const Vector& vecMaxsIn, Vector& vecMinsOut, Vector& vecMaxsOut) const;
//	inline void RotateAABB(const Vector& vecMinsIn, const Vector& vecMaxsIn, Vector& vecMinsOut, Vector& vecMaxsOut) const;
//	inline void RotateAABBByInverse(const Vector& vecMinsIn, const Vector& vecMaxsIn, Vector& vecMinsOut, Vector& vecMaxsOut) const;
//	inline void TransformPlane(const cplane_t& inPlane, cplane_t& outPlane) const;
//	inline void TransformPlaneByInverse(const cplane_t& inPlane, cplane_t& outPlane) const;
//	inline float GetOrthogonalityError() const;
//	inline float GetDeterminant()const;
//	inline float GetSylvestersCriterion()const; // for symmetrical matrices only: should be >0 iff it's a positive definite matrix
//
//	inline void InverseTR(matrix3x4_t& out) const;
//	inline matrix3x4_t InverseTR() const;
//
//
//	float* operator[](int i) { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
//	const float* operator[](int i) const { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
//	float* Base() { return &m_flMatVal[0][0]; }
//	const float* Base() const { return &m_flMatVal[0][0]; }
//
//	float m_flMatVal[3][4];
//};
//
//
//
//
//struct cplane_t;
//
//
//class VMatrix
//{
//public:
//
//	VMatrix();
//	VMatrix(
//		float m00, float m01, float m02, float m03,
//		float m10, float m11, float m12, float m13,
//		float m20, float m21, float m22, float m23,
//		float m30, float m31, float m32, float m33
//	);
//
//	// Creates a matrix where the X axis = forward
//	// the Y axis = left, and the Z axis = up
//	VMatrix(const Vector& forward, const Vector& left, const Vector& up);
//
//	// Construct from a 3x4 matrix
//	explicit VMatrix(const matrix3x4_t& matrix3x4);
//
//	// Set the values in the matrix.
//	void		Init(
//		float m00, float m01, float m02, float m03,
//		float m10, float m11, float m12, float m13,
//		float m20, float m21, float m22, float m23,
//		float m30, float m31, float m32, float m33
//	);
//
//
//	// Initialize from a 3x4
//	void		Init(const matrix3x4_t& matrix3x4);
//
//	// array access
//	inline float* operator[](int i)
//	{
//		return m[i];
//	}
//
//	inline const float* operator[](int i) const
//	{
//		return m[i];
//	}
//
//	// Get a pointer to m[0][0]
//	inline float* Base()
//	{
//		return &m[0][0];
//	}
//
//	inline const float* Base() const
//	{
//		return &m[0][0];
//	}
//
//	void		SetLeft(const Vector& vLeft);
//	void		SetUp(const Vector& vUp);
//	void		SetForward(const Vector& vForward);
//
//	void		GetBasisVectors(Vector& vForward, Vector& vLeft, Vector& vUp) const;
//	void		SetBasisVectors(const Vector& vForward, const Vector& vLeft, const Vector& vUp);
//
//	// Get/set the translation.
//	Vector& GetTranslation(Vector& vTrans) const;
//	void		SetTranslation(const Vector& vTrans);
//
//	void		PreTranslate(const Vector& vTrans);
//	void		PostTranslate(const Vector& vTrans);
//
//	matrix3x4_t& As3x4();
//	const matrix3x4_t& As3x4() const;
//	void		CopyFrom3x4(const matrix3x4_t& m3x4);
//	void		Set3x4(matrix3x4_t& matrix3x4) const;
//
//	bool		operator==(const VMatrix& src) const;
//	bool		operator!=(const VMatrix& src) const { return !(*this == src); }
//
//#ifndef VECTOR_NO_SLOW_OPERATIONS
//	// Access the basis vectors.
//	Vector		GetLeft() const;
//	Vector		GetUp() const;
//	Vector		GetForward() const;
//	Vector		GetTranslation() const;
//#endif
//
//
//	// Matrix->vector operations.
//public:
//	// Multiply by a 3D vector (same as operator*).
//	void		V3Mul(const Vector& vIn, Vector& vOut) const;
//
//	// Multiply by a 4D vector.
//	void		V4Mul(const void*& vIn, void*& vOut) const;
//
//#ifndef VECTOR_NO_SLOW_OPERATIONS
//	// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
//	Vector		ApplyRotation(const Vector& vVec) const;
//
//	// Multiply by a vector (divides by w, assumes input w is 1).
//	Vector		operator*(const Vector& vVec) const;
//
//	// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
//	Vector		VMul3x3(const Vector& vVec) const;
//
//	// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
//	Vector		VMul3x3Transpose(const Vector& vVec) const;
//
//	// Multiply by the upper 3 rows.
//	Vector		VMul4x3(const Vector& vVec) const;
//
//	// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
//	Vector		VMul4x3Transpose(const Vector& vVec) const;
//#endif
//
//
//	// Matrix->plane operations.
//public:
//	// Transform the plane. The matrix can only contain translation and rotation.
//	void		TransformPlane(const void*& inPlane, void*& outPlane) const;
//
//#ifndef VECTOR_NO_SLOW_OPERATIONS
//	// Just calls TransformPlane and returns the result.
//	void*		operator*(const void*& thePlane) const;
//#endif
//
//	// Matrix->matrix operations.
//public:
//
//	VMatrix& operator=(const VMatrix& mOther);
//
//	// Multiply two matrices (out = this * vm).
//	void		MatrixMul(const VMatrix& vm, VMatrix& out) const;
//
//	// Add two matrices.
//	const VMatrix& operator+=(const VMatrix& other);
//
//#ifndef VECTOR_NO_SLOW_OPERATIONS
//	// Just calls MatrixMul and returns the result.	
//	VMatrix		operator*(const VMatrix& mOther) const;
//
//	// Add/Subtract two matrices.
//	VMatrix		operator+(const VMatrix& other) const;
//	VMatrix		operator-(const VMatrix& other) const;
//
//	// Negation.
//	VMatrix		operator-() const;
//
//	// Return inverse matrix. Be careful because the results are undefined 
//	// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
//	VMatrix		operator~() const;
//#endif
//
//	// Matrix operations.
//public:
//	// Set to identity.
//	void		Identity();
//
//	bool		IsIdentity() const;
//
//	// Setup a matrix for origin and angles.
//	void		SetupMatrixOrgAngles(const Vector& origin, const QAngle& vAngles);
//
//	// General inverse. This may fail so check the return!
//	bool		InverseGeneral(VMatrix& vInverse) const;
//
//	// Does a fast inverse, assuming the matrix only contains translation and rotation.
//	void		InverseTR(VMatrix& mRet) const;
//
//	// Usually used for debug checks. Returns true if the upper 3x3 contains
//	// unit vectors and they are all orthogonal.
//	bool		IsRotationMatrix() const;
//
//#ifndef VECTOR_NO_SLOW_OPERATIONS
//	// This calls the other InverseTR and returns the result.
//	VMatrix		InverseTR() const;
//
//	// Get the scale of the matrix's basis vectors.
//	Vector		GetScale() const;
//
//	// (Fast) multiply by a scaling matrix setup from vScale.
//	VMatrix		Scale(const Vector& vScale);
//
//	// Normalize the basis vectors.
//	VMatrix		NormalizeBasisVectors() const;
//
//	// Transpose.
//	VMatrix		Transpose() const;
//
//	// Transpose upper-left 3x3.
//	VMatrix		Transpose3x3() const;
//#endif
//
//public:
//	// The matrix.
//	float		m[4][4];
//};
//
//inline VMatrix::VMatrix()
//{
//}
//
//inline VMatrix::VMatrix(
//	float m00, float m01, float m02, float m03,
//	float m10, float m11, float m12, float m13,
//	float m20, float m21, float m22, float m23,
//	float m30, float m31, float m32, float m33)
//{
//	Init(
//		m00, m01, m02, m03,
//		m10, m11, m12, m13,
//		m20, m21, m22, m23,
//		m30, m31, m32, m33
//	);
//}
//
//
//inline VMatrix::VMatrix(const matrix3x4_t& matrix3x4)
//{
//	Init(matrix3x4);
//}
//
//
////-----------------------------------------------------------------------------
//// Creates a matrix where the X axis = forward
//// the Y axis = left, and the Z axis = up
////-----------------------------------------------------------------------------
//inline VMatrix::VMatrix(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis)
//{
//	Init(
//		xAxis.x, yAxis.x, zAxis.x, 0.0f,
//		xAxis.y, yAxis.y, zAxis.y, 0.0f,
//		xAxis.z, yAxis.z, zAxis.z, 0.0f,
//		0.0f, 0.0f, 0.0f, 1.0f
//	);
//}
//
//
//inline void VMatrix::Init(
//	float m00, float m01, float m02, float m03,
//	float m10, float m11, float m12, float m13,
//	float m20, float m21, float m22, float m23,
//	float m30, float m31, float m32, float m33
//)
//{
//	m[0][0] = m00;
//	m[0][1] = m01;
//	m[0][2] = m02;
//	m[0][3] = m03;
//
//	m[1][0] = m10;
//	m[1][1] = m11;
//	m[1][2] = m12;
//	m[1][3] = m13;
//
//	m[2][0] = m20;
//	m[2][1] = m21;
//	m[2][2] = m22;
//	m[2][3] = m23;
//
//	m[3][0] = m30;
//	m[3][1] = m31;
//	m[3][2] = m32;
//	m[3][3] = m33;
//}
//
//
////-----------------------------------------------------------------------------
//// Initialize from a 3x4
////-----------------------------------------------------------------------------
//inline void VMatrix::Init(const matrix3x4_t& matrix3x4)
//{
//	memcpy(m, matrix3x4.Base(), sizeof(matrix3x4_t));
//
//	m[3][0] = 0.0f;
//	m[3][1] = 0.0f;
//	m[3][2] = 0.0f;
//	m[3][3] = 1.0f;
//}
//
//
////-----------------------------------------------------------------------------
//// Methods related to the basis vectors of the matrix
////-----------------------------------------------------------------------------
//
//#ifndef VECTOR_NO_SLOW_OPERATIONS
//
//inline Vector VMatrix::GetForward() const
//{
//	return Vector(m[0][0], m[1][0], m[2][0]);
//}
//
//inline Vector VMatrix::GetLeft() const
//{
//	return Vector(m[0][1], m[1][1], m[2][1]);
//}
//
//inline Vector VMatrix::GetUp() const
//{
//	return Vector(m[0][2], m[1][2], m[2][2]);
//}
//
//#endif
//
//inline void VMatrix::SetForward(const Vector& vForward)
//{
//	m[0][0] = vForward.x;
//	m[1][0] = vForward.y;
//	m[2][0] = vForward.z;
//}
//
//inline void VMatrix::SetLeft(const Vector& vLeft)
//{
//	m[0][1] = vLeft.x;
//	m[1][1] = vLeft.y;
//	m[2][1] = vLeft.z;
//}
//
//inline void VMatrix::SetUp(const Vector& vUp)
//{
//	m[0][2] = vUp.x;
//	m[1][2] = vUp.y;
//	m[2][2] = vUp.z;
//}
//
//inline void VMatrix::GetBasisVectors(Vector& vForward, Vector& vLeft, Vector& vUp) const
//{
//	vForward.Init(m[0][0], m[1][0], m[2][0]);
//	vLeft.Init(m[0][1], m[1][1], m[2][1]);
//	vUp.Init(m[0][2], m[1][2], m[2][2]);
//}
//
//inline void VMatrix::SetBasisVectors(const Vector& vForward, const Vector& vLeft, const Vector& vUp)
//{
//	SetForward(vForward);
//	SetLeft(vLeft);
//	SetUp(vUp);
//}
//
//
////-----------------------------------------------------------------------------
//// Methods related to the translation component of the matrix
////-----------------------------------------------------------------------------
//#ifndef VECTOR_NO_SLOW_OPERATIONS
//
//inline Vector VMatrix::GetTranslation() const
//{
//	return Vector(m[0][3], m[1][3], m[2][3]);
//}
//
//#endif
//
//inline Vector& VMatrix::GetTranslation(Vector& vTrans) const
//{
//	vTrans.x = m[0][3];
//	vTrans.y = m[1][3];
//	vTrans.z = m[2][3];
//	return vTrans;
//}
//
//inline void VMatrix::SetTranslation(const Vector& vTrans)
//{
//	m[0][3] = vTrans.x;
//	m[1][3] = vTrans.y;
//	m[2][3] = vTrans.z;
//}
//
//
////-----------------------------------------------------------------------------
//// appply translation to this matrix in the input space
////-----------------------------------------------------------------------------
//inline void VMatrix::PreTranslate(const Vector& vTrans)
//{
//	Vector tmp;
//	Vector3DMultiplyPosition(*this, vTrans, tmp);
//	m[0][3] = tmp.x;
//	m[1][3] = tmp.y;
//	m[2][3] = tmp.z;
//}
//
//
////-----------------------------------------------------------------------------
//// appply translation to this matrix in the output space
////-----------------------------------------------------------------------------
//inline void VMatrix::PostTranslate(const Vector& vTrans)
//{
//	m[0][3] += vTrans.x;
//	m[1][3] += vTrans.y;
//	m[2][3] += vTrans.z;
//}
//
//inline const matrix3x4_t& VMatrix::As3x4() const
//{
//	return *((const matrix3x4_t*)this);
//}
//
//inline matrix3x4_t& VMatrix::As3x4()
//{
//	return *((matrix3x4_t*)this);
//}
//
//inline void VMatrix::CopyFrom3x4(const matrix3x4_t& m3x4)
//{
//	memcpy(m, m3x4.Base(), sizeof(matrix3x4_t));
//	m[3][0] = m[3][1] = m[3][2] = 0;
//	m[3][3] = 1;
//}
//
//inline void	VMatrix::Set3x4(matrix3x4_t& matrix3x4) const
//{
//	memcpy(matrix3x4.Base(), m, sizeof(matrix3x4_t));
//}
//
//
////-----------------------------------------------------------------------------
//// Matrix math operations
////-----------------------------------------------------------------------------
//inline const VMatrix& VMatrix::operator+=(const VMatrix& other)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			m[i][j] += other.m[i][j];
//		}
//	}
//
//	return *this;
//}
//
//
//#ifndef VECTOR_NO_SLOW_OPERATIONS
//
//inline VMatrix VMatrix::operator+(const VMatrix& other) const
//{
//	VMatrix ret;
//	for (int i = 0; i < 16; i++)
//	{
//		((float*)ret.m)[i] = ((float*)m)[i] + ((float*)other.m)[i];
//	}
//	return ret;
//}
//
//inline VMatrix VMatrix::operator-(const VMatrix& other) const
//{
//	VMatrix ret;
//
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			ret.m[i][j] = m[i][j] - other.m[i][j];
//		}
//	}
//
//	return ret;
//}
//
//inline VMatrix VMatrix::operator-() const
//{
//	VMatrix ret;
//	for (int i = 0; i < 16; i++)
//	{
//		((float*)ret.m)[i] = -((float*)m)[i];
//	}
//	return ret;
//}
//
//#endif // VECTOR_NO_SLOW_OPERATIONS
//
//
////-----------------------------------------------------------------------------
//// Vector transformation
////-----------------------------------------------------------------------------
//
//#ifndef VECTOR_NO_SLOW_OPERATIONS
//
//inline Vector VMatrix::operator*(const Vector& vVec) const
//{
//	Vector vRet;
//	vRet.x = m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z + m[0][3];
//	vRet.y = m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z + m[1][3];
//	vRet.z = m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z + m[2][3];
//
//	return vRet;
//}
//
//inline Vector VMatrix::VMul4x3(const Vector& vVec) const
//{
//	Vector vResult;
//	Vector3DMultiplyPosition(*this, vVec, vResult);
//	return vResult;
//}
//
//
//inline Vector VMatrix::VMul4x3Transpose(const Vector& vVec) const
//{
//	Vector tmp = vVec;
//	tmp.x -= m[0][3];
//	tmp.y -= m[1][3];
//	tmp.z -= m[2][3];
//
//	return Vector(
//		m[0][0] * tmp.x + m[1][0] * tmp.y + m[2][0] * tmp.z,
//		m[0][1] * tmp.x + m[1][1] * tmp.y + m[2][1] * tmp.z,
//		m[0][2] * tmp.x + m[1][2] * tmp.y + m[2][2] * tmp.z
//	);
//}
//
//inline Vector VMatrix::VMul3x3(const Vector& vVec) const
//{
//	return Vector(
//		m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z,
//		m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z,
//		m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z
//	);
//}
//
//inline Vector VMatrix::VMul3x3Transpose(const Vector& vVec) const
//{
//	return Vector(
//		m[0][0] * vVec.x + m[1][0] * vVec.y + m[2][0] * vVec.z,
//		m[0][1] * vVec.x + m[1][1] * vVec.y + m[2][1] * vVec.z,
//		m[0][2] * vVec.x + m[1][2] * vVec.y + m[2][2] * vVec.z
//	);
//}
//
//#endif // VECTOR_NO_SLOW_OPERATIONS
//
//
//inline void VMatrix::V3Mul(const Vector& vIn, Vector& vOut) const
//{
//	float rw;
//
//	rw = 1.0f / (m[3][0] * vIn.x + m[3][1] * vIn.y + m[3][2] * vIn.z + m[3][3]);
//	vOut.x = (m[0][0] * vIn.x + m[0][1] * vIn.y + m[0][2] * vIn.z + m[0][3]) * rw;
//	vOut.y = (m[1][0] * vIn.x + m[1][1] * vIn.y + m[1][2] * vIn.z + m[1][3]) * rw;
//	vOut.z = (m[2][0] * vIn.x + m[2][1] * vIn.y + m[2][2] * vIn.z + m[2][3]) * rw;
//}
//
//inline void VMatrix::V4Mul(const Vector4D& vIn, Vector4D& vOut) const
//{
//	vOut[0] = m[0][0] * vIn[0] + m[0][1] * vIn[1] + m[0][2] * vIn[2] + m[0][3] * vIn[3];
//	vOut[1] = m[1][0] * vIn[0] + m[1][1] * vIn[1] + m[1][2] * vIn[2] + m[1][3] * vIn[3];
//	vOut[2] = m[2][0] * vIn[0] + m[2][1] * vIn[1] + m[2][2] * vIn[2] + m[2][3] * vIn[3];
//	vOut[3] = m[3][0] * vIn[0] + m[3][1] * vIn[1] + m[3][2] * vIn[2] + m[3][3] * vIn[3];
//}
//
//
////-----------------------------------------------------------------------------
//// Plane transformation
////-----------------------------------------------------------------------------
//inline void	VMatrix::TransformPlane(const VPlane& inPlane, VPlane& outPlane) const
//{
//	Vector vTrans;
//	Vector3DMultiply(*this, inPlane.m_Normal, outPlane.m_Normal);
//	outPlane.m_Dist = inPlane.m_Dist * DotProduct(outPlane.m_Normal, outPlane.m_Normal);
//	outPlane.m_Dist += DotProduct(outPlane.m_Normal, GetTranslation(vTrans));
//}
//
//
////-----------------------------------------------------------------------------
//// Other random stuff
////-----------------------------------------------------------------------------
//inline void VMatrix::Identity()
//{
//	MatrixSetIdentity(*this);
//}
//
//
//inline bool VMatrix::IsIdentity() const
//{
//	return
//		m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f &&
//		m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f && m[1][3] == 0.0f &&
//		m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f && m[2][3] == 0.0f &&
//		m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == 0.0f && m[3][3] == 1.0f;
//}
//



struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}
	inline Vector GetOrigin(void) const
	{
		Vector vecRet(m_flMatVal[0][3], m_flMatVal[1][3], m_flMatVal[2][3]);
		return vecRet;
	}
	const float* operator[](int i) const { return m_flMatVal[i]; }

	float m_flMatVal[3][4];
};

class VMatrix
{
public:
	float		m[4][4];

	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}

};




struct CDemoPlaybackParameters_t
{
	unsigned __int64 m_uiCaseID;
	unsigned int m_uiHeaderPrefixLength;
	unsigned int m_uiLockFirstPersonAccountID;
	bool m_bAnonymousPlayerIdentity;
	unsigned int m_numRoundSkip;
	unsigned int m_numRoundStop;
	bool m_bSkipWarmup;
	bool m_bPlayingLiveRemoteBroadcast;
	unsigned int m_uiLiveMatchID;
};

struct DemoImportantGameEvent_t
{
	int			nEventID;
	const char* pszEventName;
	const char* pszUIName;
	float		flSeekTimeBefore;			// time in seconds before the event to seek to
	float		flSeekForwardOffset;		// when searching forward to find the next instance of this event, first offset forward by this much time
	float		flSeekBackwardOffset;		// when searching backwards to find the previous instance of this event, first offset back by this much time
	bool		bScanOnly;
};

struct DemoImportantTick_t
{
	int nImportanGameEventIndex;
	int nTick;
	int nPreviousTick;
	bool bCanDirectSeek;
	KeyValues* pKeys;
};

enum SkyboxVisibility_t
{
	SKYBOX_NOT_VISIBLE = 0,
	SKYBOX_3DSKYBOX_VISIBLE,
	SKYBOX_2DSKYBOX_VISIBLE,
};


enum EngineInputContextId_t
{
	ENGINE_INPUT_CONTEXT_GAME = 0,
	ENGINE_INPUT_CONTEXT_GAMEUI,
};

enum BindingLookupOption_t
{
	BINDINGLOOKUP_ALL = -1,
	BINDINGLOOKUP_KEYBOARD_ONLY = 0,
	BINDINGLOOKUP_JOYSTICK_ONLY,
	BINDINGLOOKUP_STEAMCONTROLLER_ONLY,
};

enum
{
	JOYSTICK_MAX_BUTTON_COUNT = 32,
	JOYSTICK_POV_BUTTON_COUNT = 4,
	JOYSTICK_AXIS_BUTTON_COUNT = 0 * 2,
};

#define JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_BUTTON + ((_joystick) * JOYSTICK_MAX_BUTTON_COUNT) + (_button) )
#define JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_POV_BUTTON + ((_joystick) * JOYSTICK_POV_BUTTON_COUNT) + (_button) )
#define JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_AXIS_BUTTON + ((_joystick) * JOYSTICK_AXIS_BUTTON_COUNT) + (_button) )

#define JOYSTICK_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_POV_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_AXIS_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) )

#define MAX_JOYSTICKS = 5

//-----------------------------------------------------------------------------
// Button enum. "Buttons" are binary-state input devices (mouse buttons, keyboard keys)
//-----------------------------------------------------------------------------
enum
{
	STEAMCONTROLLER_MAX_BUTTON_COUNT = 1 - 1,
	STEAMCONTROLLER_AXIS_BUTTON_COUNT = 0 * 2,
};


enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,

	// Joystick
	JOYSTICK_FIRST = MOUSE_LAST + 1,

	JOYSTICK_FIRST_BUTTON = JOYSTICK_FIRST,
	JOYSTICK_LAST_BUTTON = -999,
	JOYSTICK_FIRST_POV_BUTTON,
	JOYSTICK_LAST_POV_BUTTON = -9999,
	JOYSTICK_FIRST_AXIS_BUTTON,
	JOYSTICK_LAST_AXIS_BUTTON = -99999,

	JOYSTICK_LAST = JOYSTICK_LAST_AXIS_BUTTON,

	STEAMCONTROLLER_FIRST = JOYSTICK_LAST + 1,

	STEAMCONTROLLER_FIRST_BUTTON = STEAMCONTROLLER_FIRST,
	STEAMCONTROLLER_LAST_BUTTON = 777777,
	STEAMCONTROLLER_FIRST_AXIS_BUTTON,
	STEAMCONTROLLER_LAST_AXIS_BUTTON = 77777777,

	STEAMCONTROLLER_LAST = STEAMCONTROLLER_LAST_AXIS_BUTTON,


	BUTTON_CODE_LAST,
	BUTTON_CODE_COUNT = BUTTON_CODE_LAST - KEY_FIRST + 1,

	// Helpers for XBox 360
	KEY_XBUTTON_UP = JOYSTICK_FIRST_POV_BUTTON,	// POV buttons
	KEY_XBUTTON_RIGHT,
	KEY_XBUTTON_DOWN,
	KEY_XBUTTON_LEFT,

	KEY_XBUTTON_A = JOYSTICK_FIRST_BUTTON,		// Buttons
	KEY_XBUTTON_B,
	KEY_XBUTTON_X,
	KEY_XBUTTON_Y,
	KEY_XBUTTON_LEFT_SHOULDER,
	KEY_XBUTTON_RIGHT_SHOULDER,
	KEY_XBUTTON_BACK,
	KEY_XBUTTON_START,
	KEY_XBUTTON_STICK1,
	KEY_XBUTTON_STICK2,
	KEY_XBUTTON_INACTIVE_START,
	KEY_XBUTTON_FIREMODE_SELECTOR_1,
	KEY_XBUTTON_FIREMODE_SELECTOR_2,
	KEY_XBUTTON_FIREMODE_SELECTOR_3,
	KEY_XBUTTON_RELOAD,
	KEY_XBUTTON_TRIGGER,
	KEY_XBUTTON_PUMP_ACTION,
	KEY_XBUTTON_ROLL_RIGHT,
	KEY_XBUTTON_ROLL_LEFT,

	KEY_XSTICK1_RIGHT = JOYSTICK_FIRST_AXIS_BUTTON,	// XAXIS POSITIVE
	KEY_XSTICK1_LEFT,							// XAXIS NEGATIVE
	KEY_XSTICK1_DOWN,							// YAXIS POSITIVE
	KEY_XSTICK1_UP,								// YAXIS NEGATIVE
	KEY_XBUTTON_LTRIGGER,						// ZAXIS POSITIVE
	KEY_XBUTTON_RTRIGGER,						// ZAXIS NEGATIVE
	KEY_XSTICK2_RIGHT,							// UAXIS POSITIVE
	KEY_XSTICK2_LEFT,							// UAXIS NEGATIVE
	KEY_XSTICK2_DOWN,							// VAXIS POSITIVE
	KEY_XSTICK2_UP,								// VAXIS NEGATIVE

	// Helpers for Steam Controller
	STEAMCONTROLLER_A = STEAMCONTROLLER_FIRST_BUTTON,
	STEAMCONTROLLER_B,
	STEAMCONTROLLER_X,
	STEAMCONTROLLER_Y,
	STEAMCONTROLLER_DPAD_UP,
	STEAMCONTROLLER_DPAD_RIGHT,
	STEAMCONTROLLER_DPAD_DOWN,
	STEAMCONTROLLER_DPAD_LEFT,
	STEAMCONTROLLER_LEFT_BUMPER,
	STEAMCONTROLLER_RIGHT_BUMPER,
	STEAMCONTROLLER_LEFT_TRIGGER,
	STEAMCONTROLLER_RIGHT_TRIGGER,
	STEAMCONTROLLER_LEFT_GRIP,
	STEAMCONTROLLER_RIGHT_GRIP,
	STEAMCONTROLLER_LEFT_PAD_FINGERDOWN,
	STEAMCONTROLLER_RIGHT_PAD_FINGERDOWN,
	STEAMCONTROLLER_LEFT_PAD_CLICK,
	STEAMCONTROLLER_RIGHT_PAD_CLICK,
	STEAMCONTROLLER_LEFT_PAD_UP,
	STEAMCONTROLLER_LEFT_PAD_RIGHT,
	STEAMCONTROLLER_LEFT_PAD_DOWN,
	STEAMCONTROLLER_LEFT_PAD_LEFT,
	STEAMCONTROLLER_RIGHT_PAD_UP,
	STEAMCONTROLLER_RIGHT_PAD_RIGHT,
	STEAMCONTROLLER_RIGHT_PAD_DOWN,
	STEAMCONTROLLER_RIGHT_PAD_LEFT,
	STEAMCONTROLLER_SELECT,
	STEAMCONTROLLER_START,
	STEAMCONTROLLER_STEAM,
	STEAMCONTROLLER_INACTIVE_START,
};

inline bool IsAlpha(ButtonCode_t code)
{
	return (code >= KEY_A) && (code <= KEY_Z);
}

inline bool IsAlphaNumeric(ButtonCode_t code)
{
	return (code >= KEY_0) && (code <= KEY_Z);
}


typedef struct player_info_s
{
	// version for future compatibility
	unsigned __int64			version;
	// network xuid
	unsigned __int64			xuid;
	// scoreboard information
	char			name[128];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[32 + 1];
	// friends identification number
	unsigned int			friendsID;
	// friends name
	char			friendsName[128];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
	// custom files CRC for this player
	void*			customFiles[32];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
} player_info_t;


class IVEngineClient
{
public:
	// Find the model's surfaces that intersect the given sphere.
	// Returns the number of surfaces filled in.
	virtual int					GetIntersectingSurfaces(
									const model_t * model,
									const Vector & vCenter,
									const float radius,
									const bool bOnlyVisibleSurfaces,	// Only return surfaces visible to vCenter.
									SurfInfo * pInfos,
									const int nMaxInfos) = 0;

	// Get the lighting intensivty for a specified point
	// If bClamp is specified, the resulting Vector is restricted to the 0.0 to 1.0 for each element
	virtual Vector				GetLightForPoint(const Vector& pos, bool bClamp) = 0;

	// Traces the line and reports the material impacted as well as the lighting information for the impact point
	virtual IMaterial* TraceLineMaterialAndLighting(const Vector& start, const Vector& end,
									Vector& diffuseLightColor, Vector& baseColor) = 0;

	// Given an input text buffer data pointer, parses a single token into the variable token and returns the new
	//  reading position
	virtual const char* ParseFile(const char* data, char* token, int maxlen) = 0;
	virtual bool				CopyLocalFile(const char* source, const char* destination) = 0;

	// Gets the dimensions of the game window
	virtual void				GetScreenSize(int& width, int& height) = 0;

	// Forwards szCmdString to the server, sent reliably if bReliable is set
	virtual void				ServerCmd(const char* szCmdString, bool bReliable = true) = 0;
	// Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
	// Note: Calls to this are checked against FCVAR_CLIENTCMD_CAN_EXECUTE (if that bit is not set, then this function can't change it).
	//       Call ClientCmd_Unrestricted to have access to FCVAR_CLIENTCMD_CAN_EXECUTE vars.
	virtual void				ClientCmd(const char* szCmdString) = 0;

	// Fill in the player info structure for the specified player index (name, model, etc.)
	virtual bool				GetPlayerInfo(int ent_num, player_info_t* pinfo) = 0;

	// Retrieve the player entity number for a specified userID
	virtual int					GetPlayerForUserID(int userID) = 0;

	// Retrieves text message system information for the specified message by name
	virtual client_textmessage_t* TextMessageGet(const char* pName) = 0;


	// Returns true if the console is visible
	virtual bool				Con_IsVisible(void) = 0;

	// Get the entity index of the local player
	virtual int					GetLocalPlayer(void) = 0;

	// Client DLL is hooking a model, loads the model into memory and returns  pointer to the model_t
	virtual const model_t* LoadModel(const char* pName, bool bProp = false) = 0;

	// Get the exact server timesstamp ( server time ) from the last message received from the server
	virtual float				GetLastTimeStamp(void) = 0;

	// Given a CAudioSource (opaque pointer), retrieve the underlying CSentence object ( stores the words, phonemes, and close
	//  captioning data )
	virtual CSentence* GetSentence(CAudioSource* pAudioSource) = 0;
	// Given a CAudioSource, determines the length of the underlying audio file (.wav, .mp3, etc.)
	virtual float				GetSentenceLength(CAudioSource* pAudioSource) = 0;
	// Returns true if the sound is streaming off of the hard disk (instead of being memory resident)
	virtual bool				IsStreaming(CAudioSource* pAudioSource) const = 0;

	// Copy current view orientation into va
	virtual void				GetViewAngles(Vector& va) = 0;
	// Set current view orientation from va
	virtual void				SetViewAngles(Vector& va) = 0;

	// Retrieve the current game's maxclients setting
	virtual int					GetMaxClients(void) = 0;

	// Given the string pBinding which may be bound to a key, 
	//  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
	virtual	const char* Key_LookupBinding(const char* pBinding) = 0;

	// Given the name of the key "mouse1", "e", "tab", etc., return the string it is bound to "+jump", "impulse 50", etc.
	virtual const char* Key_BindingForKey(ButtonCode_t code) = 0;

	// Bind a key
	virtual	void				Key_SetBinding(ButtonCode_t code, const char* pBinding) = 0;

	// key trapping (for binding keys)
	virtual void				StartKeyTrapMode(void) = 0;
	virtual bool				CheckDoneKeyTrapping(ButtonCode_t& code) = 0;

	// Returns true if the player is fully connected and active in game (i.e, not still loading)
	virtual bool				IsInGame(void) = 0;
	// Returns true if the player is connected, but not necessarily active in game (could still be loading)
	virtual bool				IsConnected(void) = 0;
	// Returns true if the loading plaque should be drawn
	virtual bool				IsDrawingLoadingImage(void) = 0;
	virtual void				HideLoadingPlaque(void) = 0;

	// Prints the formatted string to the notification area of the screen ( down the right hand edge
	//  numbered lines starting at position 0
	virtual void				Con_NPrintf(int pos, const char* fmt, ...) = 0;
	// Similar to Con_NPrintf, but allows specifying custom text color and duration information
	virtual void				Con_NXPrintf(const struct con_nprint_s* info, const char* fmt, ...) = 0;

	// Is the specified world-space bounding box inside the view frustum?
	virtual int					IsBoxVisible(const Vector& mins, const Vector& maxs) = 0;

	// Is the specified world-space boudning box in the same PVS cluster as the view origin?
	virtual int					IsBoxInViewCluster(const Vector& mins, const Vector& maxs) = 0;

	// Returns true if the specified box is outside of the view frustum and should be culled
	virtual bool				CullBox(const Vector& mins, const Vector& maxs) = 0;

	// Allow the sound system to paint additional data (during lengthy rendering operations) to prevent stuttering sound.
	virtual void				Sound_ExtraUpdate(void) = 0;
#if defined(_PS3)
	// Allow sound system updates from engine, ensure only done if sv.IsActive() is true 
	virtual void				Sound_ServerUpdateSoundsPS3(void) = 0;
#endif

	// Get the current game directory ( e.g., hl2, tf2, cstrike, hl1 )
	virtual const char* GetGameDirectory(void) = 0;

	// Get access to the world to screen transformation matrix
	virtual VMatrix& WorldToScreenMatrix() = 0;

	// Get the matrix to move a point from world space into view space
	// (translate and rotate so the camera is at the origin looking down X).
	virtual const VMatrix& WorldToViewMatrix() = 0;

	// The .bsp file can have mod-specified data lumps. These APIs are for working with such game lumps.

	// Get mod-specified lump version id for the specified game data lump
	virtual int					GameLumpVersion(int lumpId) const = 0;
	// Get the raw size of the specified game data lump.
	virtual int					GameLumpSize(int lumpId) const = 0;
	// Loads a game lump off disk, writing the data into the buffer pointed to bye pBuffer
	// Returns false if the data can't be read or the destination buffer is too small
	virtual bool				LoadGameLump(int lumpId, void* pBuffer, int size) = 0;

	// Returns the number of leaves in the level
	virtual int					LevelLeafCount() const = 0;

	// Gets a way to perform spatial queries on the BSP tree
	virtual ISpatialQuery* GetBSPTreeQuery() = 0;

	// Convert texlight to gamma...
	virtual void		LinearToGamma(float* linear, float* gamma) = 0;

	// Get the lightstyle value
	virtual float		LightStyleValue(int style) = 0;

	// Computes light due to dynamic lighting at a point
	// If the normal isn't specified, then it'll return the maximum lighting
	virtual void		ComputeDynamicLighting(const Vector& pt, const Vector* pNormal, Vector& color) = 0;

	// Returns the color of the ambient light
	virtual void		GetAmbientLightColor(Vector& color) = 0;

	// Returns the dx support level
	virtual int			GetDXSupportLevel() = 0;

	// GR - returns the HDR support status
	virtual bool        SupportsHDR() = 0;

	// Replace the engine's material system pointer.
	virtual void		Mat_Stub(IMaterialSystem* pMatSys) = 0;

	// Get the name of the current map
	virtual void GetChapterName(char* pchBuff, int iMaxLength) = 0;
	virtual char const* GetLevelName(void) = 0;
	virtual char const* GetLevelNameShort(void) = 0;
	virtual char const* GetMapGroupName(void) = 0;
#if !defined( NO_VOICE )
	// Obtain access to the voice tweaking API
	virtual struct IVoiceTweak_s* GetVoiceTweakAPI(void) = 0;
	virtual void SetVoiceCasterID(unsigned int casterID) = 0;
#endif
	// Tell engine stats gathering system that the rendering frame is beginning/ending
	virtual void		EngineStats_BeginFrame(void) = 0;
	virtual void		EngineStats_EndFrame(void) = 0;

	// This tells the engine to fire any events (temp entity messages) that it has queued up this frame. 
	// It should only be called once per frame.
	virtual void		FireEvents() = 0;

	// Returns an area index if all the leaves are in the same area. If they span multple areas, then it returns -1.
	virtual int			GetLeavesArea(unsigned short* pLeaves, int nLeaves) = 0;

	// Returns true if the box touches the specified area's frustum.
	virtual bool		DoesBoxTouchAreaFrustum(const Vector& mins, const Vector& maxs, int iArea) = 0;
	virtual int			GetFrustumList(void*** pList, int listMax) = 0;
	virtual bool		ShouldUseAreaFrustum(int area) = 0;

	// Sets the hearing origin (i.e., the origin and orientation of the listener so that the sound system can spatialize 
	//  sound appropriately ).
	virtual void		SetAudioState(const AudioState_t& state) = 0;

	// Sentences / sentence groups
	virtual int			SentenceGroupPick(int groupIndex, char* name, int nameBufLen) = 0;
	virtual int			SentenceGroupPickSequential(int groupIndex, char* name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int			SentenceIndexFromName(const char* pSentenceName) = 0;
	virtual const char* SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int			SentenceGroupIndexFromName(const char* pGroupName) = 0;
	virtual const char* SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float		SentenceLength(int sentenceIndex) = 0;

	// Computes light due to dynamic lighting at a point
	// If the normal isn't specified, then it'll return the maximum lighting
	// If pBoxColors is specified (it's an array of 6), then it'll copy the light contribution at each box side.
	virtual void		ComputeLighting(const Vector& pt, const Vector* pNormal, bool bClamp, Vector& color, Vector* pBoxColors = 0) = 0;

	// Activates/deactivates an occluder...
	virtual void		ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
	virtual bool		IsOccluded(int occlusionViewId, const Vector& vecAbsMins, const Vector& vecAbsMaxs) = 0;
	virtual int			GetOcclusionViewId() const = 0;

	// The save restore system allocates memory from a shared memory pool, use this allocator to allocate/free saverestore 
	//  memory.
	virtual void* SaveAllocMemory(size_t num, size_t size) = 0;
	virtual void		SaveFreeMemory(void* pSaveMem) = 0;

	// returns info interface for client netchannel
	virtual INetChannelInfo* GetNetChannelInfo(void) = 0;

	// Debugging functionality:
	// Very slow routine to draw a physics model
	virtual void		DebugDrawPhysCollide(const CPhysCollide* pCollide, IMaterial* pMaterial, const void*& transform, const void*& color) = 0;
	// This can be used to notify test scripts that we're at a particular spot in the code.
	virtual void		CheckPoint(const char* pName) = 0;
	// Draw portals if r_DrawPortals is set (Debugging only)
	virtual void		DrawPortals() = 0;
	// Determine whether the client is playing back or recording a demo
	virtual bool		IsPlayingDemo(void) = 0;
	virtual bool		IsRecordingDemo(void) = 0;
	virtual bool		IsPlayingTimeDemo(void) = 0;
	virtual int			GetDemoRecordingTick(void) = 0;
	virtual int			GetDemoPlaybackTick(void) = 0;
	virtual int			GetDemoPlaybackStartTick(void) = 0;
	virtual float		GetDemoPlaybackTimeScale(void) = 0;
	virtual int			GetDemoPlaybackTotalTicks(void) = 0;
	// Is the game paused?
	virtual bool		IsPaused(void) = 0;

	// What is the game timescale multiplied with the host_timescale?
	virtual float GetTimescale(void) const = 0;

	// Is the game currently taking a screenshot?
	virtual bool		IsTakingScreenshot(void) = 0;
	// Is this a HLTV broadcast ?
	virtual bool		IsHLTV(void) = 0;

#if defined( REPLAY_ENABLED )
	// Is this a Replay demo?
	virtual bool		IsReplay(void) = 0;
	// Download a replay from the given URL
	virtual void		DownloadReplay(int nReplayDownloadGroupId) = 0;
	// Is replay enabled?
	virtual bool		IsReplayEnabled() = 0;
	// Is replay recording?
	virtual bool		IsReplayRecording() = 0;
	// Get the replay recording tick from server
	virtual int			GetReplayRecordingTick() = 0;
#endif  // REPLAY_ENABLED

	// is this level loaded as just the background to the main menu? (active, but unplayable)
	virtual bool		IsLevelMainMenuBackground(void) = 0;
	// returns the name of the background level
	virtual void		GetMainMenuBackgroundName(char* dest, int destlen) = 0;

	// Occlusion system control
	virtual void		SetOcclusionParameters(const void*& params) = 0;

	// What language is the user expecting to hear .wavs in, "english" or another...
	virtual void		GetUILanguage(char* dest, int destlen) = 0;

	// Can skybox be seen from a particular point?
	virtual SkyboxVisibility_t IsSkyboxVisibleFromPoint(const Vector& vecPoint) = 0;

	// Get the pristine map entity lump string.  (e.g., used by CS to reload the map entities when restarting a round.)
	virtual const char* GetMapEntitiesString() = 0;

	// Is the engine in map edit mode ?
	virtual bool		IsInEditMode(void) = 0;

	// current screen aspect ratio (eg. 4.0f/3.0f, 16.0f/9.0f)
	virtual float		GetScreenAspectRatio(int viewportWidth, int viewportHeight) = 0;

	// allow the game UI to login a user
	virtual bool		REMOVED_SteamRefreshLogin(const char* password, bool isSecure) = 0;
	virtual bool		REMOVED_SteamProcessCall(bool& finished) = 0;

	// allow other modules to know about engine versioning (one use is a proxy for network compatability)
	virtual unsigned int	GetEngineBuildNumber() = 0; // engines build
	virtual const char* GetProductVersionString() = 0; // mods version number (steam.inf)

	// Communicates to the color correction editor that it's time to grab the pre-color corrected frame
	// Passes in the actual size of the viewport
	virtual void			GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;

	virtual bool			IsHammerRunning() const = 0;

	// Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
	// And then executes the command string immediately (vs ClientCmd() which executes in the next frame)
	//
	// Note: this is NOT checked against the FCVAR_CLIENTCMD_CAN_EXECUTE vars.
	virtual void			ExecuteClientCmd(const char* szCmdString) = 0;

	// returns if the loaded map was processed with HDR info. This will be set regardless
	// of what HDR mode the player is in.
	virtual bool MapHasHDRLighting(void) = 0;
	virtual bool MapHasLightMapAlphaData(void) = 0;

	virtual int	GetAppID() = 0;

	// Just get the leaf ambient light - no caching, no samples
	virtual Vector			GetLightForPointFast(const Vector& pos, bool bClamp) = 0;

	// This version does NOT check against FCVAR_CLIENTCMD_CAN_EXECUTE.
	virtual void			ClientCmd_Unrestricted(const char* szCmdString , bool fromConsoleOrKeybind = false) = 0;
	// Version that takes userSlot and can ignore checking if the slot validity has been set; required for joystick initialization for splitscreen
	virtual void			ClientCmd_Unrestricted(const char* szCmdString , bool fromConsoleOrKeybind, int nUserSlot, bool bCheckValidSlot = true) = 0;

	// This used to be accessible through the cl_restrict_server_commands cvar.
	// By default, Valve games restrict the server to only being able to execute commands marked with FCVAR_SERVER_CAN_EXECUTE.
	// By default, mods are allowed to execute any server commands, and they can restrict the server's ability to execute client
	// commands with this function.
	virtual void			SetRestrictServerCommands(bool bRestrict) = 0;

	// If set to true (defaults to true for Valve games and false for others), then IVEngineClient::ClientCmd
	// can only execute things marked with FCVAR_CLIENTCMD_CAN_EXECUTE.
	virtual void			SetRestrictClientCommands(bool bRestrict) = 0;

	// Sets the client renderable for an overlay's material proxy to bind to
	virtual void			SetOverlayBindProxy(int iOverlayID, void* pBindProxy) = 0;

	virtual bool			CopyFrameBufferToMaterial(const char* pMaterialName) = 0;

	// Causes the engine to read in the user's configuration on disk
	virtual void			ReadConfiguration(const int iController, const bool readDefault) = 0;

	virtual void SetAchievementMgr(IAchievementMgr* pAchievementMgr) = 0;
	virtual IAchievementMgr* GetAchievementMgr() = 0;

	virtual bool			MapLoadFailed(void) = 0;
	virtual void			SetMapLoadFailed(bool bState) = 0;

	virtual bool			IsLowViolence() = 0;
	virtual const char* GetMostRecentSaveGame(bool bEnsureExists = false) = 0;
	virtual void			SetMostRecentSaveGame(const char* lpszFilename) = 0;

	virtual void			StartXboxExitingProcess() = 0;

	virtual bool			IsSaveInProgress() = 0;
	virtual bool			IsAutoSaveDangerousInProgress() = 0;

	virtual unsigned int			OnStorageDeviceAttached(int iController) = 0;
	virtual void			OnStorageDeviceDetached(int iController) = 0;

	virtual const char* GetSaveDirName() = 0; // get a pointer to the path where saves should go (with a trailing slash already added)

	// generic screenshot writing
	virtual void			WriteScreenshot(const char* pFilename) = 0;

	virtual void			ResetDemoInterpolation(void) = 0;

	// For non-split screen games this will always be zero
		virtual int				GetActiveSplitScreenPlayerSlot() = 0;
		virtual int				SetActiveSplitScreenPlayerSlot(int slot) = 0;

		// This is the current # of players on the local host
		virtual bool			SetLocalPlayerIsResolvable(char const* pchContext, int nLine, bool bResolvable) = 0;
		virtual bool			IsLocalPlayerResolvable() = 0;

		virtual int				GetSplitScreenPlayer(int nSlot) = 0;
		virtual bool			IsSplitScreenActive() = 0;
		virtual bool			IsValidSplitScreenSlot(int nSlot) = 0;
		virtual int				FirstValidSplitScreenSlot() = 0; // -1 == invalid
		virtual int				NextValidSplitScreenSlot(int nPreviousSlot) = 0; // -1 == invalid

		//Finds or Creates a shared memory space, the returned pointer will automatically be AddRef()ed
		virtual ISPSharedMemory* GetSinglePlayerSharedMemorySpace(const char* szName, int ent_num = 66) = 0;

		// Computes an ambient cube that includes ALL dynamic lights
		virtual void ComputeLightingCube(const Vector& pt, bool bClamp, Vector* pBoxColors) = 0;

		//All callbacks have to be registered before demo recording begins. TODO: Macro'ize a way to do it at startup
		virtual void RegisterDemoCustomDataCallback(void* szCallbackSaveID, void* pCallback) = 0;
		virtual void RecordDemoCustomData(void* pCallback, const void* pData, size_t iDataLength) = 0;

		// global sound pitch scaling
		virtual void SetPitchScale(float flPitchScale) = 0;
		virtual float GetPitchScale(void) = 0;

		// Load/unload the SFM - used by Replay
		virtual bool		LoadFilmmaker() = 0;
		virtual void		UnloadFilmmaker() = 0;

		// leaf flag management. Allows fast leaf enumeration of leaves that have a flag set

		// set a bit in a leaf flag
		virtual void SetLeafFlag(int nLeafIndex, int nFlagBits) = 0;

		// you must call this once done modifying flags. Not super fast.
		virtual void RecalculateBSPLeafFlags(void) = 0;

		virtual bool DSPGetCurrentDASRoomNew(void) = 0;
		virtual bool DSPGetCurrentDASRoomChanged(void) = 0;
		virtual bool DSPGetCurrentDASRoomSkyAbove(void) = 0;
		virtual float DSPGetCurrentDASRoomSkyPercent(void) = 0;
		virtual void SetMixGroupOfCurrentMixer(const char* szgroupname, const char* szparam, float val, int setMixerType) = 0;
		virtual int GetMixLayerIndex(const char* szmixlayername) = 0;
		virtual void SetMixLayerLevel(int index, float level) = 0;
		virtual int GetMixGroupIndex(const char* pMixGroupName) = 0;
		virtual void SetMixLayerTriggerFactor(int nMixLayerIndex, int nMixGroupIndex, float flFactor) = 0;
		virtual void SetMixLayerTriggerFactor(const char* pMixLayerIndex, const char* pMixGroupIndex, float flFactor) = 0;

		virtual bool IsCreatingReslist() = 0;
		virtual bool IsCreatingXboxReslist() = 0;

		virtual void SetTimescale(float flTimescale) = 0;

		// Methods to set/get a gamestats data container so client & server running in same process can send combined data
		virtual void SetGamestatsData(CGamestatsData* pGamestatsData) = 0;
		virtual CGamestatsData* GetGamestatsData() = 0;

	#if defined( USE_SDL ) || defined( OSX )
		// we need to pull delta's from the cocoa mgr, the engine vectors this for us
		virtual void GetMouseDelta(int& x, int& y, bool bIgnoreNextMouseDelta = false) = 0;
	#endif

		// Given the string pBinding which may be bound to a key, 
		//  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
		// Increment start count to iterate through multiple keys bound to the same binding
		// iAllowJoystick defaults to -1 witch returns joystick and non-joystick binds, 0 returns only non-joystick, 1 returns only joystick
		virtual	const char* Key_LookupBindingEx(const char* pBinding, int iUserId = -1, int iStartCount = 0, BindingLookupOption_t nFlags = BINDINGLOOKUP_ALL) = 0;

		// returns key_code for specified binding
		virtual int	Key_CodeForBinding(const char* pBinding, int iUserId = -1, int iStartCount = 0, BindingLookupOption_t nFlags = BINDINGLOOKUP_ALL) = 0;

		// Updates dynamic light state. Necessary for light cache to work properly for d- and elights
		virtual void UpdateDAndELights(void) = 0;

		// Methods to get bug count for internal dev work stat tracking.
		// Will get the bug count and clear it every map transition
		virtual int			GetBugSubmissionCount() const = 0;
		virtual void		ClearBugSubmissionCount() = 0;

		// Is there water anywhere in the level?
		virtual bool	DoesLevelContainWater() const = 0;

		// How much time was spent in server simulation?
		virtual float	GetServerSimulationFrameTime() const = 0;

		virtual void SolidMoved(class IClientEntity* pSolidEnt, class ICollideable* pSolidCollide, const Vector* pPrevAbsOrigin, bool accurateBboxTriggerChecks) = 0;
		virtual void TriggerMoved(class IClientEntity* pTriggerEnt, bool accurateBboxTriggerChecks) = 0;

		// Using area bits, check whether the area of the specified point flows into the other areas
		virtual void ComputeLeavesConnected(const Vector& vecOrigin, int nCount, const int* pLeafIndices, bool* pIsConnected) = 0;

		// Is the engine in Commentary mode?
		virtual bool IsInCommentaryMode(void) = 0;

		virtual void SetBlurFade(float amount) = 0;
		virtual bool IsTransitioningToLoad() = 0;

		virtual void SearchPathsChangedAfterInstall() = 0;

		virtual void ConfigureSystemLevel(int nCPULevel, int nGPULevel) = 0;

		virtual void SetConnectionPassword(char const* pchCurrentPW) = 0;

		virtual CSteamAPIContext* GetSteamAPIContext() = 0;

		virtual void SubmitStatRecord(char const* szMapName, unsigned int uiBlobVersion, unsigned int uiBlobSize, const void* pvBlob) = 0;

		// Sends a key values server command, not allowed from scripts execution
		// Params:
		//	pKeyValues	- key values to be serialized and sent to server
		//				  the pointer is deleted inside the function: pKeyValues->deleteThis()
		virtual void ServerCmdKeyValues(KeyValues* pKeyValues) = 0;
		virtual void SendMessageToServer(INetMessage* pMessage, bool bForceReliable = false, bool bVoice = false) = 0;
		// Tells the engine what and where to paint
		virtual bool SpherePaintSurface(const model_t* pModel, const Vector& vPosition, char color, float flSphereRadius, float flPaintCoatPercent) = 0;
		virtual bool HasPaintmap() = 0;
		// Enable paint in the engine for project Paint
		virtual void EnablePaintmapRender() = 0;
		virtual void SphereTracePaintSurface(const model_t* pModel, const Vector& vPosition, const Vector& vContactNormal, float flSphereRadius, void*& surfColors) = 0;
		virtual void RemoveAllPaint() = 0;
		virtual void PaintAllSurfaces(char color) = 0;
		virtual void RemovePaint(const model_t* pModel) = 0;

		virtual bool IsActiveApp() = 0;

		// is this client running inside the same process as an active server?
		virtual bool IsClientLocalToActiveServer() = 0;

		// Callback for LevelInit to tick the progress bar during time consuming operations
		virtual void TickProgressBar() = 0;

		// Returns the requested input context
		virtual void* GetInputContext(void* id) = 0;

		virtual void GetStartupImage(char* pOutBuff, int nOutBuffSize) = 0;

		// For the rare case when the client DLL needs to do something different if network backdoor is on.
		virtual bool IsUsingLocalNetworkBackdoor() = 0;

		virtual bool SaveGame(const char* pSaveFilename, bool bIsXSave, char* pOutName, int nOutNameSize, char* pOutComment, int nOutCommentSize) = 0;

		// Request 'generic' memory stats (returns a list of N named values; caller should assume this list will change over time)
		virtual int GetGenericMemoryStats(void*** ppMemoryStats) = 0;

		// On exit from a map, this becomes true once all map-related assets are flushed from memory:
		virtual bool GameHasShutdownAndFlushedMemory() = 0;

		//get the command_number from the most recent command the server acknowledged processing
		virtual int GetLastAcknowledgedCommand(void) = 0;

		virtual void FinishContainerWrites(int iController) = 0;

		virtual void FinishAsyncSave() = 0;

		virtual int GetServerTick(void) = 0;

		// return the final directory in the game dir (i.e "cstrike", "hl2", rather than c:\blah\cstrike )
		virtual const char* GetModDirectory(void) = 0;

		virtual void AudioLanguageChanged() = 0;

		virtual bool IsAutoSaveInProgress() = 0;

		virtual void StartLoadingScreenForCommand(const char* command) = 0;

		virtual void StartLoadingScreenForKeyValues(KeyValues* keyValues) = 0;

		// Sos opvars
		virtual bool SOSSetOpvarFloat(const char* pOpVarName, float flValue) = 0;
		virtual bool SOSGetOpvarFloat(const char* pOpVarName, float& flValue) = 0;

	#if defined(_PS3)
			virtual void* GetHostStateWorldBrush(void) = 0;
		virtual bool PS3_IsUserRestrictedFromChat(void) = 0;
		virtual bool PS3_IsUserRestrictedFromOnline(void) = 0;
		virtual bool PS3_PendingInvitesFound(void) = 0;
		virtual void PS3_ShowInviteOverlay(void) = 0;

		virtual bool  bOverrideCSMConvars(void) = 0;
		virtual bool  bDrawWorldIntoCSM(void) = 0;
		virtual bool  bDrawStaticPropsIntoCSM(void) = 0;
		virtual float GetCSMMaxDist(void) = 0;
	#endif

		virtual bool IsSubscribedMap(const char* pchMapName, bool bOnlyOnDisk) = 0;
		virtual bool IsFeaturedMap(const char* pchMapName, bool bOnlyOnDisk) = 0;

		// Access demo playback parameters
		virtual CDemoPlaybackParameters_t const* GetDemoPlaybackParameters() = 0;

		// Client version from the steam.inf, this will be compared to the GC version
		virtual int GetClientVersion() const = 0; // engines build

		virtual bool IsDemoSkipping() = 0;
		virtual void SetDemoImportantEventData(const KeyValues* pData) = 0;
		// clear any temp entity events that are stacked up
		virtual void ClearEvents() = 0;

		virtual float GetSafeZoneXMin(void) const = 0;

		virtual bool IsVoiceRecording() const = 0;
		virtual void ForceVoiceRecordOn() const = 0;

		virtual int GetConnectionDataProtocol() const = 0;

		virtual bool EngineGotvSyncPacket(const CEngineGotvSyncPacket* pPkt) = 0;

		virtual const char* AliasToCommandString(const char* szAliasName) = 0;
};
