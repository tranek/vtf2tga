#include <iostream>
#include <VTFLib13/VTFLib.h>
#include <VTFLib13/VTFFile.h>
#include <Magick++.h>

using namespace Magick;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Incorrect arguments." << std::endl;
		std::cout << "Arg 1 = /path/to/.vtf file." << std::endl;
		std::cout << "Arg 2 = /output/directory." << std::endl;
		exit(1);
	}

	VTFLib::CVTFFile vtf;

    if (!vtf.Load(argv[1]))
	{
		std::cout << "Failed to load .vtf file." << std::endl;
        exit(1);
    }

	std::cout << "Loading: " << argv[1] << std::endl;

	vlUInt width = vtf.GetWidth();
    vlUInt height = vtf.GetHeight();
	vlUInt depth  = vtf.GetDepth();

	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;

	std::string img_dimensions = std::to_string(width) + "x" + std::to_string(height);
	std::cout << "Dimensions: " << img_dimensions << std::endl;

	VTFImageFormat srcformat = vtf.GetFormat();
	VTFImageFormat dstformat;

	int img_dstformat = 0;

	if (VTFLib::CVTFFile::GetImageFormatInfo(srcformat).uiAlphaBitsPerPixel > 0)
	{
        dstformat = IMAGE_FORMAT_RGBA8888;
		img_dstformat = 1;
	}
	else
	{
		dstformat = IMAGE_FORMAT_RGB888;
		img_dstformat = 0;
	}

	if (img_dstformat == 1) {
		std::cout << "Destination format: RGBA" << std::endl;
	} else {
		std::cout << "Destination format: RGB" << std::endl;
	}

	int currentFrame = 0;

	const vlByte* frame = vtf.GetData(currentFrame, 0, 0, 0);

    if (!frame) {
		std::cout << "Failed to get the image data at frame 0." << std::endl;
        exit(1);
    }

	Image image;
	image.type(::Magick::TrueColorType);
	image.modifyImage();

	// memory copy vtflib's buffer to image magick's buffer
	VTFLib::CVTFFile tmpfile;
	tmpfile.Create(vtf.GetWidth(), vtf.GetHeight());
	vtf.ConvertToRGBA8888(vtf.GetData(1,1,1,0), tmpfile.GetData(1,1,1,0), vtf.GetWidth(), vtf.GetHeight(), vtf.GetFormat());
    
	image.read(tmpfile.GetWidth(), tmpfile.GetHeight(), "RGBA", Magick::CharPixel, tmpfile.GetData(1,1,1,0));


	std::cout << "Writing: " << argv[2] << std::endl;

	image.magick("TGA");
	image.write(argv[2]);


	exit(0);
}
