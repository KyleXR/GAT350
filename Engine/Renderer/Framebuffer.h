#pragma once
#include "Renderer.h"
#include "Resource/Resource.h"

namespace neu
{
	class Texture;

	class Framebuffer : public Resource
	{
	public:
		~Framebuffer();

		bool Create(std::string filename, ...) override;
		bool CreateFramebuffer();
		bool CreateDepthbuffer(int width, int height);

		void Bind();
		void Unbind();

		glm::ivec2 GetSize() const { return { m_width, m_height }; }

		int m_width = 0;
		int m_height = 0;

	protected:

		GLuint m_fbo = 0;
		std::shared_ptr<Texture> m_texture;
	};
}