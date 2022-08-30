1. soure->target transformation
Eigen::Matrix4f transformation;
transformation << 0.9980, 0.0523, 0.0349, 1.000,
				-0.0552,0.9947,0.0871,2.000,
				-0.0302,0.0889,0.9956,3.000,
				0.0000,0.0000,0.0000,0.0000;
2. 粗配准矩阵
Eigen::Matrix4f Initial_transformation;
Initial_transformation<<0.992731,  0.0703799, -0.0976327,    0.81838,
				-0.0804302,   0.991409,  -0.103145,    1.75992,
				0.0895346,   0.110248,   0.989863,     3.0017,
				0,          0,          0,          1;