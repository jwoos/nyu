from PIL import Image as image, ImageDraw as image_draw, ImageFont as image_font
import random

background_rgb = tuple([random.randint(0, 255) for x in range(3)])
base = image.new('RGB', (500, 650), background_rgb)

name = input('Please input a name: ')
font = image_font.truetype('roboto.ttf', 48)
context = image_draw.Draw(base)
text_x, text_y = context.textsize(name, font=font)
context.text(((500 - text_x) / 2, 550), name, font=font)

back_rgb = tuple([random.randint(0, 255) for _ in range(3)])
context.rectangle([(75, 75), (425, 425)], fill=back_rgb)

face_file = image.open('smiley.png')
base.paste(face_file, (150, 150), face_file)

base.show()
