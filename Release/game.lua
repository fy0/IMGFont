
-- ����������ɫ�ͱ�����ɫ
flux.SetFontColor(255, 0, 0)
flux.SetBackgroundColor(255,255,255,0)

-- �����о�
flux.SetLineGap(-3)

fp = io.open('charlist.txt', 'r')
txt = fp:read()
fp:close()

-- ��������������ֿ�ͼƬ
font = flux.LoadFont("wqy-microhei.ttc", "wqy", 20, 1)
ret = flux.MakeGlyph(font, txt, 256)

-- ��ӡ������Ϣ
print('�ַ���','����','X','Y','��','��','��߾�','�ұ߾�')
for k,v in pairs(ret:getchs()) do
	print(v.ch, v.index, v.x, v.y, v.width, v.height, v.left, v.xadvance)
end

-- ����Ϊ PNG
flux.ImgSave(ret.img, flux.IL_PNG, "output.png")

-- ����� JPG
flux.ImgSave(ret.img, flux.IL_JPG, "output.jpg")

-- ����� TGA
flux.ImgSave(ret.img, flux.IL_TGA, "output.tga")

-- ����� DDS
flux.ImgSave(ret.img, flux.IL_DDS, "output.dds")

print('done')
