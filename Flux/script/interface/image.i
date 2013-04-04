
void ImgSave(ILuint imgID, ILenum fileformat, const string& filename);

void SetBackgroundColor(int R, int G, int B, int A=0xFF);
void SetFontColor(int R, int G, int B, int A=0xFF);

Color GetBackgroundColor();
Color GetFontColor();

class Color {
public:
	Color() : R(0),G(0),B(0),A(0xFF) {};
	Color(byte R, byte G, byte B, byte A) : R(R),G(G),B(B),A(A) {};
	byte R,G,B,A;
};
