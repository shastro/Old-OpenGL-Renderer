import bpy



context = bpy.context
f = open("lights.txt", 'w+')



objects = bpy.context.scene.objects

for obj in objects:
	obj.select = obj.type == "EMPTY"


for obj in context.selected_objects:
	out = str(obj.location.x) + " " + str(obj.location.y) + " " + str(obj.location.z) + "\n"
	f.write(out) 