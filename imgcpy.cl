__kernel void imgcpy(__read_only image2d_t imgIn, __write_only image2d_t imgOut)
{
    const sampler_t sampler     =   CLK_NORMALIZED_COORDS_FALSE | 
                                    CLK_ADDRESS_CLAMP_TO_EDGE | 
                                    CLK_FILTER_NEAREST;

    const int2 pos              =   { 
                                        get_global_id(0), 
                                        get_global_id(1)
                                    };

    uint4 pixel                 =   read_imageui(imgIn,sampler,pos);

    write_imageui(imgOut, pos, pixel);
}
