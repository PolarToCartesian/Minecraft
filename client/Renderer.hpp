#pragma once

#include <client/Window.hpp>

namespace mc {

	static VKAPI_ATTR VkBool32 VKAPI_CALL RendererVulkanValidationCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData) {

		REPORT_WARNING << pCallbackData->pMessage;

		return VK_FALSE;
	}

	class Renderer {
	private:
		vk::UniqueInstance m_instance;

#ifdef _DEBUG
		vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic> m_debugUtilsMessenger;
#endif // _DEBUG

		vk::UniqueSurfaceKHR m_surface;

	public:
		Renderer(const mc::Window& window) noexcept;
	};

}; // namespace mc