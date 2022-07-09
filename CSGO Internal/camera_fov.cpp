#include "camera.h"

void Camera::SetupFOV(CViewSetup* view)
{
	view->fov = Settings::Camera::FOV;
}