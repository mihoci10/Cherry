#pragma once

#include <glm/glm.hpp>

namespace Cherry{

	enum class ShaderSourceType {
		None, Vertex, Fragment
	};

    class Shader {
	public:

		Shader() = delete;
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniform(const std::string_view& name, int value) = 0;
		virtual void SetUniform(const std::string_view& name, float value) = 0;
		virtual void SetUniform(const std::string_view& name, const glm::vec2& value) = 0;
		virtual void SetUniform(const std::string_view& name, const glm::vec3& value) = 0;
		virtual void SetUniform(const std::string_view& name, const glm::vec4& value) = 0;
		virtual void SetUniform(const std::string_view& name, const glm::mat4& value) = 0;
		virtual void SetUniformArray(const std::string_view& name, int* values, uint32_t count) = 0;

		inline const std::string& GetName() const { return m_Name; };
		inline const std::string& GetSource(ShaderSourceType sourceType) const { return m_Sources.at(sourceType); }

		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

	protected:
		Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
			: m_Name(name), m_Sources{ { ShaderSourceType::Vertex, vertexSrc }, { ShaderSourceType::Fragment, fragmentSrc } }
		{}

		std::string m_Name;
		std::unordered_map<ShaderSourceType, std::string> m_Sources;

	};
    
}