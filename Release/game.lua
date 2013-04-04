
-- 设置字体颜色和背景颜色
flux.SetFontColor(255, 0, 0)
flux.SetBackgroundColor(255,255,255,0)

-- 设置行距
flux.SetLineGap(-3)

fp = io.open('charlist.txt', 'r')
txt = fp:read()
fp:close()

-- 加载字体和生成字库图片
font = flux.LoadFont("wqy-microhei.ttc", "wqy", 20, 1)
ret = flux.MakeGlyph(font, txt, 256)

-- 打印文字信息
print('字符码','索引','X','Y','宽','高','左边距','右边距')
for k,v in pairs(ret:getchs()) do
	print(v.ch, v.index, v.x, v.y, v.width, v.height, v.left, v.xadvance)
end

-- 保存为 PNG
flux.ImgSave(ret.img, flux.IL_PNG, "output.png")

-- 保存成 JPG
flux.ImgSave(ret.img, flux.IL_JPG, "output.jpg")

-- 保存成 TGA
flux.ImgSave(ret.img, flux.IL_TGA, "output.tga")

-- 保存成 DDS
flux.ImgSave(ret.img, flux.IL_DDS, "output.dds")

print('done')
