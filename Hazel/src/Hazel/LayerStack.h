#pragma once

#include <vector>

#include "Hazel/Core.h"							//include macros
#include "Layer.h"				


namespace Hazel {

	class HAZEL_API LayerStack					//HAZEL_API macro for __dllexport
	{
	public:
		LayerStack();							//declare layerstack
		~LayerStack();							//destry layerstack

		void PushLayer(Layer* layer);			//push layer at the end of layerstack
		void PushOverlay(Layer* overlay);		//push overlay at the end of layerstack
		void PopLayer(Layer* layer);			//remove layer
		void PopOverlay(Layer* overlay);		//remove overlay

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }		//??
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }			//??
	private:
		std::vector<Layer*> m_Layers;											//??
		unsigned int m_LayerInsertIndex = 0;									//total of layers
	};

}