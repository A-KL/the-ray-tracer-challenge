import yaml

def get_cpp_var_name(base_name, cpp_data):
    if base_name in cpp_data['var_names']:
        cpp_data['var_names'][base_name] += 1
        return f"{base_name}{cpp_data['var_names'][base_name]}"
    else:
        cpp_data['var_names'][base_name] = 1
        return base_name

def define_material(yaml_data, cpp_data):
    name = yaml_data.get('define', 'default_material').replace("-", "_")
    value = yaml_data.get('value', None)
    

    default_material = {
        'color': [1, 1, 1],
        'ambient': 0.1,
        'diffuse': 0.9,
        'specular': 0.9,
        'shininess': 200,
        'reflective': 0.0,
        'transparency': 0.0,
    }

    if 'extend' in yaml_data:
        base_define_name = yaml_data['extend'].replace("-", "_")
        base_material = cpp_data['shared_defines'].get(base_define_name, default_material)

        default_material['ambient'] = base_material.get('ambient', default_material['ambient'])
        default_material['diffuse'] = base_material.get('diffuse', default_material['diffuse'])
        default_material['specular'] = base_material.get('specular', default_material['specular'])
        default_material['shininess'] = base_material.get('shininess', default_material['shininess'])
        default_material['reflective'] = base_material.get('reflective', default_material['reflective'])
        default_material['transparency'] = base_material.get('transparency', default_material['transparency'])
    else:
        cpp_data['shared_defines'][name] = value

    color = value.get('color', default_material['color'])
    ambient = value.get('ambient', default_material['ambient'])
    diffuse = value.get('diffuse', default_material['diffuse'])
    specular = value.get('specular', default_material['specular'])
    shininess = value.get('shininess', default_material['shininess'])
    reflective = value.get('reflective', default_material['reflective'])
    transparency = value.get('transparency', default_material['transparency'])

    if "Color3D" not in cpp_data['includes']:
        cpp_data['includes'].append("Color3D")

    if "Material3D" not in cpp_data['includes']:
        cpp_data['includes'].append("Material3D")

    cpp_data['lines'].append(f"auto {name} = ");
    cpp_data['lines'].append(f"   Material3D(SolidColor3D(Color3D({color[0]}, {color[1]}, {color[2]})), {ambient}, {diffuse}, {specular}, {shininess}, {reflective}, {transparency});\n")
    
    print(f"Material3D parameters: color={color}, ambient={ambient}, diffuse={diffuse}, specular={specular}, shininess={shininess}")

def define_transform(yaml_data, cpp_data):
    # Placeholder for transform definition
    # You can implement the logic to define transformations based on the YAML data
    pass

def define_object(yaml_data, cpp_data):
    if "material" in yaml_data['define']:
        define_material(yaml_data, cpp_data)   
    if "transform" in yaml_data['define']:
        define_transform(yaml_data, cpp_data)

def add_camera(yaml_data, cpp_data):
    width = yaml_data.get('width', 100)
    height = yaml_data.get('height', 100)
    field_of_view = yaml_data.get('field-of-view', 0.785)
    from_point = yaml_data.get('from', [0, 0, 0])
    to_point = yaml_data.get('to', [0, 0, -1])
    up_vector = yaml_data.get('up', [0, 1, 0])

    if "Camera" not in cpp_data['includes']:
        cpp_data['includes'].append("Camera")

    name = get_cpp_var_name("camera", cpp_data)

    cpp_data['lines'].append(f"auto {name} = ");
    cpp_data['lines'].append(f"   Camera({width}, {height}, {field_of_view}, Point3D({from_point[0]}, {from_point[1]}, {from_point[2]}), Point3D({to_point[0]}, {to_point[1]}, {to_point[2]}), Vector3D({up_vector[0]}, {up_vector[1]}, {up_vector[2]}));\n")
                             
    print(f"Camera parameters: width={width}, height={height}, field_of_view={field_of_view}, from={from_point}, to={to_point}, up={up_vector}")

def add_light(yaml_data, cpp_data):
    at = yaml_data.get('at', [0, 0, 0])
    intensity = yaml_data.get('intensity', [1, 1, 1])

    if "Color3D" not in cpp_data['includes']:
        cpp_data['includes'].append("Color3D")

    if "Light3D" not in cpp_data['includes']:
        cpp_data['includes'].append("Light3D")


    name = get_cpp_var_name("light", cpp_data)

    cpp_data['lines'].append(f"auto {name} = ");
    cpp_data['lines'].append(f"   Light3D(Point3D({at[0]}, {at[1]}, {at[2]}), Color3D({intensity[0]}, {intensity[1]}, {intensity[2]}));\n")

    cpp_data['lines'].append(f"{cpp_data['scene_name']}.Lights.push_back(&{name});\n")
    
    print(f"Light parameters: at={at}, intensity={intensity}")

def main():

  types_map = {
    "camera": add_camera,
    "light": add_light,
    "define": define_object,

    # "plane": "Plane3D",
    # "cylinder": "Cylinder3D",
    # "sphere": "Sphere3D",
    # "cube": "Cube3D",
  }

  cpp_data = {
      "var_names": {},
      "includes":[],
      "lines":[],
      "scene_name": "scene",
      "shared_defines": {}
  }
  
  with open("./cover.yml") as input_file:
      try:
          input = yaml.safe_load(input_file)
          #
          # Process each item in the YAML input
          #
          for item in input:
              if "define" in item:
                  define_func = types_map.get("define")

                  if (define_func is not None):
                    define_func(item, cpp_data)
              
              if "add" in item:
                  yaml_type = item['add']
                  add_func = types_map.get(yaml_type)

                  if (add_func is not None):
                    add_func(item, cpp_data)

          #
          # Output the generated C++ code to a file
          #
          with open("./cover.cpp", "w") as output_file:

              # Standard C++ includes
              output_file.write("#include <iostream>\n")

              # Ray tracer C++ includes
              output_file.write("#include \"../lib/Core/Color3D.h\"\n")
              output_file.write("#include \"../lib/Core/Scene3D.h\"\n")
              output_file.write("#include \"../lib/Core/Canvas.h\"\n")


              # Include the necessary headers for the objects being created
              for include in cpp_data['includes']:
                  output_file.write(f"#include \"../lib/Core/{include}.h\"\n")

              # The function definition
              output_file.write("\nvoid run_cover_demo(Canvas& canvas) {\n")

              output_file.write("\n    const int w = canvas.Width();")
              output_file.write("\n    const int h = canvas.Height();\n")
              output_file.write("\n    Scene3D scene;\n\n")

              # Generated C++ code lines
              for line in cpp_data['lines']:
                  output_file.write(f"    {line}\n")

              output_file.write(f"\n    camera.Render({cpp_data['scene_name']}, canvas);\n")
              output_file.write("}\n")

      except yaml.YAMLError as exc:
          print(exc)

if __name__ == "__main__":
    main()