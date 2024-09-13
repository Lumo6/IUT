/*!
 *
 * \brief Déclaration de la classe CMatrice. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2015
 * \version 1.1
 */

#include <vector>
#include <ostream>

class CMatrice {
private:
	std::vector<std::vector<double>> m_vvdData;
public:
	CMatrice();
	CMatrice(size_t,size_t);
	size_t GetNbCols();
	size_t GetNbRows();
	double& operator() (size_t, size_t);
	CMatrice& Zeros();
	CMatrice& Identity();
	bool operator== (CMatrice&);
	bool operator!= (CMatrice&);
	CMatrice operator- ();
	CMatrice operator- (CMatrice&);
	CMatrice& operator-= (CMatrice&);
	CMatrice operator+ (CMatrice&);
	CMatrice& operator+= (CMatrice&);
	CMatrice operator* (CMatrice&);
};

std::ostream& operator<<(std::ostream&, CMatrice&);