#include "Camera.h"
#include "Trig.h"
#include "Scale.h"
#include "Trans.h"

#include <cstdio>

Camera::Camera()
	: 
	//DNode(), 
	id(Camera::ID::Uninitialized), 
	aspectRatio(0), 
	farDist(0), 
	fovy(0), 
	nearDist(0),
	cbCameraData(sizeof(Mat4) * 2)
{}

/*bool Camera::Compare(Node* pTargetNode)
{
	assert(pTargetNode);
	Camera* pTargetCamera = (Camera*)pTargetNode;
	assert(pTargetCamera);
	return this->id == pTargetCamera->id;
}*/
//void Camera::Print()
//{
//	DNode::Print();
//	std::printf("	camera ID: %d\n", this->id);
//	std::printf("	direction: (%.1f, %.1f, %.1f)\n", dirVec.x(), dirVec.y(), dirVec.z());
//	std::printf("	look at vector: (%.1f, %.1f, %.1f)\n", vLookAt.x(), vLookAt.y(), vLookAt.z());
//	std::printf("	right vector: (%.1f, %.1f, %.1f)\n", rightVec.x(), rightVec.y(), rightVec.z());
//	std::printf("	up vector: (%.1f, %.1f, %.1f)\n", upVec.x(), upVec.y(), upVec.z());
//}

void Camera::Update()
{
	this->UpdateProjectionMatrix();
	this->UpdateViewMatrix();

	// Transfer the camera data from the struct into the buffer.
	cbCameraData.Transfer(&cameraData);
	// Tell the constant buffer to send data to the GPU.
	cbCameraData.SetActive(ConstantBufferSlot::CameraData);
}

Mat4 &Camera::GetViewMat(void)
{
	return this->viewMat;
}
Mat4 &Camera::GetProjMat(void)
{
	return this->projMat;
}
void Camera::GetPosVec(Vec3 &outPos) const
{
	outPos = this->posVec;
}
void  Camera::GetDirVec(Vec3 &outDir) const
{
	outDir = this->dirVec;
}
void  Camera::GetUpVec(Vec3 &outUp) const
{
	outUp = this->upVec;
}
void Camera::GetLookAtVec(Vec3 &outLookAt) const
{
	outLookAt = this->lookAtVec;
}
void Camera::GetRightVec(Vec3 &outRight) const
{
	outRight = this->rightVec;
}
void Camera::Set(Camera::ID inID)
{
	this->id = inID;
}
void Camera::SetPerspective(const float fovDegs, const float inAspectRatio, 
	const float inNearDist, const float inFarDist)
{
	this->aspectRatio = inAspectRatio;
	this->fovy = MATH_PI_180 * fovDegs;
	this->nearDist = inNearDist;
	this->farDist = inFarDist;
};
void Camera::SetOrientAndPosition(const Vec3 &inUpVec, const Vec3 &inLookAtVec, 
	const Vec3 &inPosVec)
{
	// The upVec, dirVec and rightVec are unit length and perpendicular. Find the right 
	// vector, then correct Up to insure perpendicular. Make sure that all vectors are 
	// unit vectors.
	this->lookAtVec = inLookAtVec;
	
	this->dirVec = -(inLookAtVec - inPosVec); // Right-Hand camera: dirVec is flipped.
	this->dirVec.norm();
	
	this->rightVec = inUpVec.cross(this->dirVec);
	this->rightVec.norm();
	
	this->upVec = this->dirVec.cross(this->rightVec);
	this->upVec.norm();
	
	this->posVec = inPosVec;
};

void Camera::UpdateProjectionMatrix(void)
{
	float d = 1 / Trig::tan(fovy / 2);

	this->projMat[m0] = d / aspectRatio;
	this->projMat[m1] = 0.0f;
	this->projMat[m2] = 0.0f;
	this->projMat[m3] = 0.0f;
	this->projMat[m4] = 0.0f;
	this->projMat[m5] = d;
	this->projMat[m6] = 0.0f;
	this->projMat[m7] = 0.0f;
	this->projMat[m8] = 0.0f;
	this->projMat[m9] = 0.0f;
	this->projMat[m10] = -(this->farDist + this->nearDist) / (this->farDist - this->nearDist);
	this->projMat[m11] = -1.0f;
	this->projMat[m12] = 0.0f;
	this->projMat[m13] = 0.0f;
	this->projMat[m14] = (-2.0f * this->farDist * this->nearDist) / 
		(this->farDist - this->nearDist);
	this->projMat[m15] = 0.0f;

	// Converting from OpenGL-style NDC of [-1,1] to DX's [0,1].  
	// See note: https://anteru.net/blog/2011/12/27/1830/
	Trans B(0.0f, 0.0f, 1.0f);
	Scale S(1.0f, 1.0f, 0.5f);
	this->projMat = this->projMat * B * S;

	this->cameraData.proj = this->projMat;
};
void Camera::UpdateViewMatrix(void)
{
	// This functions assumes that upVec, rightVec, and dirVec are unit vectors and 
	// are perpendicular to each other.
	// Set for DX right-handed space.
	this->viewMat[m0] = this->rightVec[x];
	this->viewMat[m1] = this->upVec[x];
	this->viewMat[m2] = this->dirVec[x];
	this->viewMat[m3] = 0.0f;
	this->viewMat[m4] = this->rightVec[y];
	this->viewMat[m5] = this->upVec[y];
	this->viewMat[m6] = this->dirVec[y];
	this->viewMat[m7] = 0.0f;
	this->viewMat[m8] = this->rightVec[z];
	this->viewMat[m9] = this->upVec[z];
	this->viewMat[m10] = this->dirVec[z];
	this->viewMat[m11] = 0.0f;
	// Apply R^t( -Pos ). Use dot-product with the basis vectors.
	this->viewMat[m12] = -posVec.dot(rightVec);
	this->viewMat[m13] = -posVec.dot(upVec);
	this->viewMat[m14] = -posVec.dot(dirVec);
	this->viewMat[m15] = 1.0f;

	this->cameraData.view = this->viewMat;
};
