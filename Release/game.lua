
-- ����������ɫ�ͱ�����ɫ
flux.SetFontColor(255, 0, 0)
flux.SetBackgroundColor(255,255,255,0)

-- �����о�
flux.SetLineGap(-3)
-- �����и�(ǿ��ָ��ÿ�и߶ȣ��Ḳ���о�����)
-- flux.SetLineHeight(50)

fp = io.open('charlist.txt', 'r')
txt = fp:read()
fp:close()

-- ��������������ֿ�ͼƬ
font = flux.LoadFont("wqy-microhei.ttc", "wqy", 20, 1)
ret = flux.MakeGlyph(font, txt, 256)
chs = ret:getchs()

-- ��ӡ�ֿ���Ϣ
print(string.format("\nͼƬ���: %d, ͼƬ�߶�: %d\n", ret.width, ret.height))

-- ��ӡ�ַ���Ϣ
print('�ַ���','����','X','Y','��','��','��߾�','�ұ߾�','�ϱ߾�', '�±߾�')
for k,v in pairs(chs) do
	print(v.ch, v.index, v.x, v.y, v.width, v.height, v.left, v.right, v.top, v.bottom)
end

-- �����ַ���ϢΪ����������
fp = io.open('out.fnt', 'wb')
for k,v in pairs(chs) do
	-- �ַ�����Ϊ˫�ֽڵ� short(h)�������˸���������Ϊ int
	fp:write(struct.pack('hiiiiiiii', v.ch, v.x, v.y, v.width, v.height, v.left, v.right, v.top, v.bottom))
end
fp:close()

-- ����Ϊ PNG
flux.ImgSave(ret.img, flux.IL_PNG, "output.png")

-- ����� JPG
flux.ImgSave(ret.img, flux.IL_JPG, "output.jpg")

-- ����� TGA
flux.ImgSave(ret.img, flux.IL_TGA, "output.tga")

-- ����� DDS
flux.ImgSave(ret.img, flux.IL_DDS, "output.dds")

print('done')
