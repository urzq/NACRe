#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include <GL/glew.h>

class Program
{
public:
	Program(const char * vertex_file_path, const char * fragment_file_path);
	~Program();

	void Use();
	void Disable();

	GLuint GetUniformLocation(const char* name) const;

private:
	GLuint m_ProgramID;
};

#endif