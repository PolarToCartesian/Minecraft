#include <client/Renderer.hpp>

#define RENDERER_VK_RV_ASSERT(rvName, funcRet, errorMsg)     \
	auto rvName = funcRet;                                   \
	ASSERT(rvName.result == vk::Result::eSuccess, errorMsg);

#define RRVKRVAT(rvName, funcRet, errorMsg) RENDERER_VK_RV_ASSERT(rvName, funcRet, errorMsg)

#define RENDERER_VK_UNIQUE_CREATION_HANDLER(innerName, funcRet, errorMsg) \
	{                                                                     \
		RENDERER_VK_RV_ASSERT(innerName##RV, funcRet, errorMsg);          \
		innerName = std::move((innerName##RV).value);             \
	}

#define RRVKUECNHR(innerName, funcRet, errorMsg) RENDERER_VK_UNIQUE_CREATION_HANDLER(innerName, funcRet, errorMsg)

namespace mc {

	Renderer::Renderer(const mc::Window& window) noexcept {
		constexpr std::array requiredExtensions = {
			"VK_KHR_surface",
#ifdef _WIN32
			"VK_KHR_win32_surface",
#endif // _WIN32
#ifdef _DEBUG
			VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif // _DEBUG
		};

#ifdef _DEBUG
		constexpr std::array<const char*, 1u> requiredLayers = {
			"VK_LAYER_KHRONOS_validation"
		};
#else
		constexpr std::array<const char*, 1u> requiredLayers = {  };
#endif

		{ // Instance
			// Test If All Required Extensions Are Present
			RRVKRVAT(presentExtensionPropertiesRV, vk::enumerateInstanceExtensionProperties(), "Failed to get enumerate extension propreties from vulkan");

			for (const char* const requiredExtension : requiredExtensions) {
				bool bFound = false;
				
				for (const vk::ExtensionProperties& pep : presentExtensionPropertiesRV.value) {
					if (!std::strcmp(requiredExtension, pep.extensionName)) {
						bFound = true;
						break;
					}
				}

				if (bFound)
					continue;

				ABORT("A required Vulkan extension is not present");
			}

			// Test If All Required Layers Are Present
			RRVKRVAT(presentLayerPropertiesRV, vk::enumerateInstanceLayerProperties(), "Failed to enumerate instance layer propreties from vulkan");
			
			for (const char* const requiredLayer : requiredLayers) {
				bool bFound = false;

				for (vk::LayerProperties& plp : presentLayerPropertiesRV.value) {
					if (!std::strcmp(requiredLayer, plp.layerName)) {
						bFound = true;
						break;
					}
				}

				if (bFound)
					continue;

				ABORT("A required Vulkan layer is not present");
			}

			// Create Instance
			vk::ApplicationInfo appInfo{};
			appInfo.apiVersion         = VK_VERSION_1_2;
			appInfo.pApplicationName   = "Minecraft Client";
			appInfo.applicationVersion = MINECRAFT_VERSION;
			appInfo.engineVersion      = NULL;
			appInfo.pEngineName        = NULL;

			vk::InstanceCreateInfo ici{};
			ici.pApplicationInfo        = &appInfo;
			ici.ppEnabledExtensionNames = requiredExtensions.data();
			ici.enabledExtensionCount   = static_cast<mc::u32>(requiredExtensions.size());
			ici.ppEnabledLayerNames     = requiredLayers.data();
			ici.enabledLayerCount       = static_cast<mc::u32>(requiredLayers.size());

			RRVKUECNHR(m_instance, vk::createInstanceUnique(ici), "Failed to create a Vulkan Instance");
		}

		{ // Setup Debug Callback
#ifdef _DEBUG
			vk::DebugUtilsMessengerCreateInfoEXT dumci{};
			dumci.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
			dumci.messageType     = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
			dumci.pfnUserCallback = mc::RendererVulkanValidationCallback;

			vk::DispatchLoaderDynamic dldy;
			dldy.init(*this->m_instance);

			auto r = this->m_instance->createDebugUtilsMessengerEXTUnique(dumci, nullptr, dldy);
			std::cout << (int)r.result << '\n';


			//RRVKUECNHR(m_debugUtilsMessenger, , "Failed to setup a Vulkan Debug Utils Messenger");
#endif // _DEBUG
		}

		{ // Create Surface
#ifdef _WIN32
			vk::Win32SurfaceCreateInfoKHR w32sci;

			w32sci.hinstance = GetModuleHandleA(NULL);
			w32sci.hwnd      = window.GetNativeHandle();

			RRVKUECNHR(m_surface, this->m_instance->createWin32SurfaceKHRUnique(w32sci), "Failed to create a Vulkan Surface");
#endif // _WIN32
		}

		{

		}

		{

		}
	}

}; // namespace mc