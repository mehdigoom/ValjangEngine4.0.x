/*************************************************************************/
/*  sphere_shape_3d.h                                                    */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      http://Valjang.fr                          */
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

#ifndef SPHERE_SHAPE_3D_H
#define SPHERE_SHAPE_3D_H

#include "scene/resources/shape_3d.h"

class SphereShape3D : public Shape3D {
	GDCLASS(SphereShape3D, Shape3D);
	float radius;

protected:
	static void _bind_methods();

	virtual void _update_shape() override;

public:
	void set_radius(float p_radius);
	float get_radius() const;

	virtual Vector<Vector3> get_debug_mesh_lines() override;
	virtual real_t get_enclosing_radius() const override;

	SphereShape3D();
};

#endif // SPHERE_SHAPE_H
