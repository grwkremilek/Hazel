#include "hzpch.h"								//include a collection of standard library header files
#include "LayerStack.h"							

namespace Hazel {

	LayerStack::LayerStack()					//constructor
	{
	}

	LayerStack::~LayerStack()					//destructor
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);		//push layer at the end of stack
		m_LayerInsertIndex++;												//total of layers
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);									// insert a new element at the end of the vector container
	}

	void LayerStack::PopLayer(Layer* layer)								//remove layer
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)							//remove overlay
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
		
	}
}