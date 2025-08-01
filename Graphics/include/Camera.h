#ifndef CAMERA_H
#define CAMERA_H

#include "ConstantBuffer.h"
#include "Mat4.h"
#include "Vec3.h"
//#include "DNode.h"

class Camera //final : public DNode
{
public:
	enum class ID
	{
		A,
		B,
		C,
		D,
		Null,
		Uninitialized
	};
	
	Camera::ID id;

	Camera();
	Camera(const Camera& rhs) = delete;
	Camera& operator = (const Camera& rhs) = delete;
	~Camera() = default;

	//virtual bool Compare(Node* pTargetNode) override;
	//virtual void Print() override;

	void Update();
	
	Mat4& GetViewMat();
	Mat4& GetProjMat();
	void GetPosVec(Vec3& outPosVec) const;
	void GetDirVec(Vec3& outDirVec) const;
	void GetUpVec(Vec3& outUpVec) const;
	void GetLookAtVec(Vec3& outLookAtVec) const;
	void GetRightVec(Vec3& outRightVec) const;
	void Set(Camera::ID inID);
	void SetPerspective(const float fovDegs, const float inAspectRatio, 
		const float inNearDist, const float inFarDist);
	void SetOrientAndPosition(const Vec3& inUpVect, const Vec3& inLookAtVec, 
		const Vec3& inPosVec);

private:  
	Mat4 projMat;
	Mat4 viewMat;
	Vec3 upVec;
	Vec3 dirVec;
	Vec3 rightVec;  
	Vec3 posVec;
	Vec3 lookAtVec;
	float nearDist;
	float farDist;
	float fovy;  
	float aspectRatio;
	 
	// Struct used to load the camera data into CBCameraData.	
	CameraData cameraData;
	
	ConstantBuffer cbCameraData;
	
	void UpdateProjectionMatrix();
	void UpdateViewMatrix();
};

#endif
