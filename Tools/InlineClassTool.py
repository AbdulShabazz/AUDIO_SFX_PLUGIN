import re

description = '''
Here's a possible implementation of the Python module that reads 
the C++20 header class file and its implementation file and returns 
a new header file with all class member methods and attributes inlined:
'''

def inline_class(header_file, impl_file):
    # read header file
    with open(header_file, 'r') as f:
        header_text = f.read()
    # read implementation file
    with open(impl_file, 'r') as f:
        impl_text = f.read()
    # extract class name
    class_name_match = re.search(r'class\s+(\w+)\s*{', header_text)
    if not class_name_match:
        raise ValueError('Class name not found in header file')
    class_name = class_name_match.group(1)
    # extract public methods
    method_regex = r'^\s*(\w+)\s+(\w+)\s*\((.*)\);'
    method_matches = re.finditer(method_regex, header_text, re.MULTILINE)
    methods = []
    for method_match in method_matches:
        if method_match.group(1) == 'void' and method_match.group(2) != class_name:
            # ignore non-constructor void methods (assume they have implementations in the CPP file)
            methods.append((method_match.group(1), method_match.group(2), method_match.group(3)))
    # extract attributes
    attribute_regex = r'^\s*(\w+)\s+(\w+)\s*;'
    attribute_matches = re.finditer(attribute_regex, header_text, re.MULTILINE)
    attributes = []
    for attribute_match in attribute_matches:
        attributes.append((attribute_match.group(1), attribute_match.group(2)))
    # extract method implementation
    method_impl_regex = r'^\s*void\s+' + class_name + '::(\w+)\((.*)\)\s*\{\s*(.*?)\s*\}'
    method_impl_matches = re.finditer(method_impl_regex, impl_text, re.DOTALL)
    method_impls = {}
    for method_impl_match in method_impl_matches:
        method_name = method_impl_match.group(1)
        method_body = method_impl_match.group(3)
        method_impls[method_name] = method_body
    # generate inline header text
    inline_text = f'class {class_name}\n{{\npublic:\n'
    for attr_type, attr_name in attributes:
        inline_text += f'    {attr_type} {attr_name};\n'
    for method_type, method_name, method_params in methods:
        if method_name in method_impls:
            method_body = method_impls[method_name]
        else:
            method_body = '; // implementation not found'
        inline_text += f'    {method_type} {method_name}({method_params}) {{ {method_body} }}\n'
    inline_text += '};\n'
    return inline_text
