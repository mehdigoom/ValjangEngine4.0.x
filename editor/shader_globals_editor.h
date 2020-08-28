/*************************************************************************/
/*  shader_globals_editor.h                                              */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Valjang.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef SHADER_GLOBALS_EDITOR_H
#define SHADER_GLOBALS_EDITOR_H

#include "core/undo_redo.h"
#include "editor/editor_autoload_settings.h"
#include "editor/editor_data.h"
#include "editor/editor_plugin_settings.h"
#include "editor/editor_sectioned_inspector.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/tab_container.h"

class ShaderGlobalsEditorInterface;

class ShaderGlobalsEditor : public VBoxContainer {
	GDCLASS(ShaderGlobalsEditor, VBoxContainer)

	ShaderGlobalsEditorInterface *interface;
	EditorInspector *inspector;

	LineEdit *variable_name;
	OptionButton *variable_type;
	Button *variable_add;

	void _variable_added();
	void _variable_deleted(const String &p_variable);
	void _changed();

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	ShaderGlobalsEditor();
	~ShaderGlobalsEditor();
};

#endif // SHADER_GLOBALS_EDITOR_H
