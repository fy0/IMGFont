
-- 设置字体颜色和背景颜色
flux.SetFontColor(255, 0, 0)
flux.SetBackgroundColor(255,255,255,0)

-- 设置行距
flux.SetLineGap(-3)
-- 设置行高(强制指定每行高度，会覆盖行距设置)
-- flux.SetLineHeight(50)

fp = io.open('charlist.txt', 'r')
txt = fp:read()
fp:close()

-- 加载字体和生成字库图片
font = flux.LoadFont("wqy-microhei.ttc", "wqy", 20, 1)
ret = flux.MakeGlyph(font, txt, 256)
chs = ret:getchs()

-- 打印字库信息
print(string.format("\n图片宽度: %d, 图片高度: %d\n", ret.width, ret.height))

-- 打印字符信息
print('字符码','索引','X','Y','宽','高','左边距','右边距','上边距', '下边距')
for k,v in pairs(chs) do
	print(v.ch, v.index, v.x, v.y, v.width, v.height, v.left, v.right, v.top, v.bottom)
end

-- 保存字符信息为二进制数据
fp = io.open('out.fnt', 'wb')
for k,v in pairs(chs) do
	-- 字符保存为双字节的 short(h)，其他八个参数保存为 int
	fp:write(struct.pack('hiiiiiiii', v.ch, v.x, v.y, v.width, v.height, v.left, v.right, v.top, v.bottom))
end
fp:close()

-- 保存为 PNG
flux.ImgSave(ret.img, flux.IL_PNG, "output.png")

-- 保存成 JPG
flux.ImgSave(ret.img, flux.IL_JPG, "output.jpg")

-- 保存成 TGA
flux.ImgSave(ret.img, flux.IL_TGA, "output.tga")

-- 保存成 DDS
flux.ImgSave(ret.img, flux.IL_DDS, "output.dds")

print('done')
