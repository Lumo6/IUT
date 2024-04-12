/*!
 * \file "TP.cpp"
 * 
 * \version 2016
 *
 * \brief Définition de la classe CTP
 */
#include "StdAfx.h"
#define _USE_MATH_DEFINES
#include "TP.h"
#include "incLibGraph2.h"

/*!
 * \brief Affiche les objets.
 * 
 * \todo Afficher tous les objets.
 */
void CTP::Afficher() const
{
	for (auto& forme : m_ListePointerForm)
		forme->Afficher();
}

/*!
 * \brief Définit les attributs graphiques des prochains objets créés.
 *
 * La fonction affiche une boîte de dialogue pour sélectionner graphiquement 
 * les attributs des formes. Les attibuts sont la couleur du trait, son 
 * épaisseur ainsi que son style d'affichage.
 */
void CTP::GuiSetDefaultStyle()
{
  LibGraph2::GetLibGraph2()->guiGetPenStyle(m_argbCurColor, m_fCurThickness, m_eCurStyle);
}

/*!
 * \brief Définit les attributs graphiques des prochains objets créés.
 *
 * La fonction affiche une boîte de dialogue pour sélectionner graphiquement 
 * la couleur de remplissage.
 */
void CTP::GuiSetDefaultFill()
{
  LibGraph2::GetLibGraph2()->guiGetColor(m_argbCurFill);
}

/*!
 * \brief
 * Ajoute un nouvelle forme.
 * 
 * \param to
 * Type d'objet à créer.
 * 
 * \param ptP1
 * Point d'origine de la nouvelle forme.
 * 
 * \remark 
 * La forme est créée sans définir son point d'arrivée car la fonction 
 * ModifierDerniereForme va être appelée juste après.
 *
 * \todo Ajouter une nouvelle forme ayant les caratéristiques suivantes : \n
 * - Le type de forme spécifié par le paramètre \c to
 * - Le point d'origine en \c ptP1 \n
 * - Les attributs de tracés courant \n
 * - La couleur de remplissage courant \n
 * - Les attributs spécifiques des formes ne sont pas définis \n
 * - Le point d'arrivée n'est pas encore défini
 */
void CTP::AjouterForme(TypeObjet to, const LibGraph2::CPoint& ptP1)
{
	std::shared_ptr<CForme> pForme;

	switch (to)
	{
	case CTP::TypeObjet::TypeRectangle:
		pForme = std::make_shared<CRect>();
		break;
	case CTP::TypeObjet::TypeEllipse:
		pForme = std::make_shared<CEllispse>();
		break;
	case CTP::TypeObjet::TypeArc:
		pForme = std::make_shared<CArc>();
		break;
	default:
		break;
	}

	pForme->SetP1(ptP1);
	pForme->SetColor(m_argbCurColor);
	pForme->SetThickness(m_fCurThickness);
	pForme->SetStyle(m_eCurStyle);
	pForme->SetFillColor(m_argbCurFill);

	m_ListePointerForm.push_back(pForme);
}

/*!
 * \brief
 * Définit le point d'arrivée de la dernière forme créée.
 * 
 * \param ptP2
 * Point d'arrivé de la dernière forme créée.
 * 
 * \todo Modifier de la dernière forme créée pour lui affecter son point d'arrivée à \c ptP2
 */
void CTP::ModifierDerniereForme(const LibGraph2::CPoint& ptP2)
{
	if (m_ListePointerForm.size() != 0)
		m_ListePointerForm.back()->SetP2(ptP2);
}

/*!
 * \brief
 * Définit l'angle de départ du dernier arc créé.
 *
 * L'angle de départ de l'arc est calculé à partir du point \c pt passé en 
 * paramètre. L'angle calculé est l'angle que réalise le vecteur qui part du 
 * centre de l'ellipse vers le point \c pt avec l'horizontale. Pour calculer 
 * cet angle, il suffit d'appliquer l'équation suivante :
 * \f[
 * a = \text{ atan2 } \left( \vec{ v }_y, \vec{ v }_x \right) * \frac{ 180 }{ \pi }
 * \f]
 * où \f$ \vec{v} \f$ est le vecteur du centre de l'ellipse vers le point \c pt.
 * 
 * \param pt
 * Point de destination du vecteur définissant l'angle de départ de l'arc.
 * 
 * \todo Modifier le dernier arc créé pour lui affecter son angle de départ en 
 * suivant les indications précédentes.
 * 
 */
void CTP::ModifierDernierArcStartAngle(const LibGraph2::CPoint& pt)
{
	std::shared_ptr<CArc> pArc;
	pArc = std::dynamic_pointer_cast<CArc>(m_ListePointerForm.back());

	if (pArc) {
		LibGraph2::CPoint vecteur;

		LibGraph2::CPoint centre;
		centre.m_fX = (m_ListePointerForm.back()->GetBounds().m_ptTopLeft.m_fX + m_ListePointerForm.back()->GetBounds().m_ptTopLeft.m_fX + m_ListePointerForm.back()->GetBounds().m_szSize.m_fWidth) / 2;
		centre.m_fY = (m_ListePointerForm.back()->GetBounds().m_ptTopLeft.m_fY + m_ListePointerForm.back()->GetBounds().m_ptTopLeft.m_fY + m_ListePointerForm.back()->GetBounds().m_szSize.m_fHeight) / 2;

		vecteur.m_fX = pt.m_fX - centre.m_fX;
		vecteur.m_fY = pt.m_fY - centre.m_fY;

		double a = std::atan2(vecteur.m_fY, vecteur.m_fX) * 180.0 / M_PI;
		pArc->SetStartAngle((float)a);
	}
}

/*!
 * \brief
 * Définit l'angle de balayage du dernier arc créé.
 *
 * L'angle de balayage de l'arc est calculé à partir du point \c pt passé en
 * paramètre. L'angle calculé est l'angle que réalise le vecteur qui part du 
 * centre de l'ellipse vers le point \c pt avec l'horizontale auquel on 
 * retranche l'angle de départ. Pour calculer cet angle, il suffit d'appliquer
 * les équations suivantes :
 *
 * \f[
 * a_{temp} = \text{ atan2 } \left( \vec{ v }_y, \vec{ v }_x \right) * \frac{ 180 }{ \pi } - a_{start}
 * \f]
 * \f[
 * a=\begin{cases}
 *     a_{temp}, & \text{ si }a_{temp}>=0 \text{ , } \\
 *     a_{temp} + 360, & \text{ sinon} 
 *   \end{cases}
 * \f]
 *
 * où \f$ \vec{v} \f$ est le vecteur du centre de l'ellipse vers le point \c pt 
 * et \f$ a_{start} \f$ est l'angle de départ de l'arc.
 * 
 * \param pt
 * Point de destination du vecteur définissant l'angle de balayage de l'arc.
 * 
 * \todo Modifier le dernier arc créé pour lui affecter son angle de balayage en 
 * suivant les indications précédentes.
 * 
 */
void CTP::ModifierDernierArcSweepAngle(const LibGraph2::CPoint& pt)
{
	std::shared_ptr<CArc> pArc;
	pArc = std::dynamic_pointer_cast<CArc>(m_ListePointerForm.back());

	if (pArc) {
		LibGraph2::CPoint vecteur;

		LibGraph2::CPoint centre;
		centre.m_fX = (m_ListePointerForm.back()->GetBounds().m_ptTopLeft.m_fX + m_ListePointerForm.back()->GetBounds().m_ptTopLeft.m_fX + m_ListePointerForm.back()->GetBounds().m_szSize.m_fWidth) / 2;
		centre.m_fY = (m_ListePointerForm.back()->GetBounds().m_ptTopLeft.m_fY + m_ListePointerForm.back()->GetBounds().m_ptTopLeft.m_fY + m_ListePointerForm.back()->GetBounds().m_szSize.m_fHeight) / 2;

		vecteur.m_fX = pt.m_fX - centre.m_fX;
		vecteur.m_fY = pt.m_fY - centre.m_fY;


		double a_temp = (std::atan2(vecteur.m_fY, vecteur.m_fX) * 180.0 / M_PI) - pArc->GetStartAngle();
		double a = a_temp >= 0 ? a_temp : a_temp + 360;
		pArc->SetSweepAngle((float)a);
	}
}

/*!
 * \brief
 * Place la forme du fond en premier plan.
 *
 * \todo Décaler vers le début du tableau toutes les formes. La première forme 
 * doit alors être placée en fin de tableau.
 * 
 */
void CTP::MettreEnPremierPlan()
{
	if (m_ListePointerForm.size() <= 1)
		return;

	std::swap(m_ListePointerForm.front(), m_ListePointerForm.back());

	auto itAvantDernier = std::prev(--m_ListePointerForm.end());

	while (itAvantDernier != m_ListePointerForm.begin()) {
		std::swap(*itAvantDernier, *std::prev(itAvantDernier));
		--itAvantDernier;
	}
}

/*!
 * \brief
 * Place la forme du premier plan en fond.
 *
 * \todo Décaler vers la fin du tableau toutes les formes. La dernière forme 
 * doit alors être placée en début de tableau.
 * 
 */
void CTP::MettreEnArrierePlan()
{
	if (m_ListePointerForm.size() <= 1)
		return;

	std::swap(m_ListePointerForm.front(), m_ListePointerForm.back());

	auto itSuivant = std::next(m_ListePointerForm.begin());

	while (itSuivant != --m_ListePointerForm.end()) {
		std::swap(*itSuivant, *std::next(itSuivant));
		++itSuivant;
	}
}
