/*  Valeria Frolova, UVic
	Sep 23, 2020
	
	Function is used for finding ray-triangle intersection point, in 3D space.
	If no intersection found, assign all 0's to intersection point and return false
	*/
using namespace std;
// Vector Struct
struct Vector3{
float X;
float Y;
float Z;
};

// A simple poly
struct Poly{
Vector3 P1;
Vector3 P2;
Vector3 P3;
};

bool DoesIntersect(Vector3 location, Vector3 velocity, Poly testTri, Vector3 &intersectPoint){
/*
  Ray-triangle intersection is given as an inverse of the system, formed by:
  ray(L) = location + L*velocity = p1+a(p2-p1)+b(p3-p1), where L is what we must obtain
  This results in a matrix system that is solved by finding vector: marker=[a,b,L]
  
  Then, if (a and b)>=0 AND (a + b)<=1, then ray intersects the triangle
*/
 Vector3* p=&intersectPoint;
//fill in matrix, since vectors and points are not accessed iteratively
	float k[3][3];
	k[0][0] = -(testTri.P2.X-testTri.P1.X);
	k[0][1] = -(testTri.P3.X-testTri.P1.X);
	k[0][2] = velocity.X;
	k[1][0] = -(testTri.P2.Y-testTri.P1.Y);
	k[1][1] = -(testTri.P3.Y-testTri.P1.Y);
	k[1][2] = velocity.Y;
	k[2][0] = -(testTri.P2.Z-testTri.P1.Z);
	k[2][1] = -(testTri.P3.Z-testTri.P1.Z);
	k[2][2] = velocity.Z;
//find matrix inverse "k" (rewrites itself)
	k=inv(k);
//multiply inverted matrix with vector v = [p1-location], where P could be any point of the triangle (?)
//I think I should choose "location" as it forms origin of the ray
	float v[3] = {testTri.P1.X-location.X,testTri.P1.Y-location.Y,testTri.P1.Z-location.Z};
	float * marker = mult_matrices(k,v); //[a,b,L]
//check if condition holds: if a,b>=0 AND a+b<=1, then ray intersects the triangle
	if (*(marker)>=0 && *(marker+1)>=0 && (*(marker)+*(marker+1))<=1){
	//intersectsPoint must now hold the point of intersection which is given as:
		//line equation solution with the "L"=marker[2]
		p.X = location.X+*(marker+2)*velocity.X;
		p.Y = location.Y+*(marker+2)*velocity.Y;
		p.Z = location.Z+*(marker+2)*velocity.Z;
		return true;
	}
	else {
		//no intersection. set to 0
		p.X = 0;
		p.Y = 0;
		p.Z = 0;
		return false;
	}
}
//function for finding matrix inverse
float* inv(float mat[][]){
	//find determinant
	for(int i=0; i<3; i++)
		det = det + (mat[0][i] * (mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3] * mat[2][(i+1)%3]));
	for(int i=0; i<3; i++){ //original matrix gets replaced with its inverse (not assuming non-existent inverse)
		for(int j=0; j<3; j++)
			mat[i][j]=((mat[(j+1)%3][(i+1)%3] * mat[(j+2)%3][(i+2)%3]) - (mat[(j+1)%3][(i+2)%3] * mat[(j+2)%3][(i+1)%3]))/ determinant<<"\t";
	}
	return mat;
}
//multiplication of matrix and a vector - error check not introduced
float * mult_matrices(float m1[][],float m2[]){//we multiply matrix by a vector in this case
	float mat[]={0,0,0};
	for(int i=0;i<3;i++){
		for(int j=0;i<3;i++)
		mat[i]+=m1[i][j]*m2[j]; //3x3 matrix multiplication onto 3x1 vector
	}
	return mat; //return vector as a reference
}
