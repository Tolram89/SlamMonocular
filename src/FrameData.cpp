#include "../include/FrameData.hpp"
#include <stdexcept>

FrameData::FrameData(int id, const cv::Mat& image, std::shared_ptr<const Camera> camera)
	:id(id), image(image), camera(std::move(camera))
{
	if (this->image.empty())
		throw std::runtime_error("Image is empty");
	if (!this->camera) {
		throw std::invalid_argument("Camera is null");
	}
}