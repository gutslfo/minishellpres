/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:42:38 by pitran            #+#    #+#             */
/*   Updated: 2025/05/20 15:48:21 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void demonstrate_ast_construction_for_eval(void)
{
    printf("DÉMONSTRATION AST POUR ÉVALUATION\n");
    printf("==================================\n\n");
    
    printf("INPUT: \"echo hello | grep h && echo found\"\n\n");
    
    printf("ÉTAPE 1: TOKENISATION\n");
    printf("---------------------\n");
    printf("[0] WORD:\"echo\"  [1] WORD:\"hello\"  [2] PIPE:\"|\"  [3] WORD:\"grep\"\n");
    printf("[4] WORD:\"h\"     [5] AND:\"&&\"      [6] WORD:\"echo\" [7] WORD:\"found\"\n\n");
    
    printf("ÉTAPE 2: ANALYSE PRÉCÉDENCE\n");
    printf("---------------------------\n");
    printf("Opérateurs trouvés:\n");
    printf("- Position 2: | (précédence 2)\n");
    printf("- Position 5: && (précédence 1) ← PLUS FAIBLE = RACINE\n\n");
    
    printf("ÉTAPE 3: CONSTRUCTION RÉCURSIVE\n");
    printf("-------------------------------\n");
    printf("create_operator_node(NODE_AND_IF,\n");
    printf("  parse(0,4),  ← \"echo hello | grep h\"\n");
    printf("  parse(6,7)   ← \"echo found\"\n");
    printf(")\n\n");
    
    printf("BRANCHE GAUCHE: parse(0,4) = \"echo hello | grep h\"\n");
    printf("→ Trouve | en position 2\n");
    printf("→ create_operator_node(NODE_PIPE,\n");
    printf("    parse(0,1),  ← \"echo hello\"\n");
    printf("    parse(3,4)   ← \"grep h\"\n");
    printf("  )\n\n");
    
    printf("FEUILLES:\n");
    printf("- parse(0,1): NODE_CMD args=[\"echo\",\"hello\",NULL]\n");
    printf("- parse(3,4): NODE_CMD args=[\"grep\",\"h\",NULL]\n");
    printf("- parse(6,7): NODE_CMD args=[\"echo\",\"found\",NULL]\n\n");
    
    printf("ÉTAPE 4: AST FINAL (à dessiner au tableau)\n");
    printf("==========================================\n");
    printf("                NODE_AND_IF\n");
    printf("               /           \\\n");
    printf("          NODE_PIPE    NODE_CMD(echo found)\n");
    printf("         /        \\\n");
    printf("  NODE_CMD      NODE_CMD\n");
    printf("(echo hello)   (grep h)\n\n");
    
    printf("ÉTAPE 5: VÉRIFICATION STRUCTURE\n");
    printf("===============================\n");
    printf("root->type = NODE_AND_IF\n");
    printf("root->children[0]->type = NODE_PIPE\n");
    printf("root->children[1]->type = NODE_CMD\n");
    printf("root->children[2] = NULL\n\n");
    
    printf("POINTS CLÉS POUR L'ÉVAL:\n");
    printf("1. Précédence détermine la forme de l'arbre\n");
    printf("2. Récursion divise le problème en sous-problèmes\n");
    printf("3. Chaque type de nœud utilise différemment la structure\n");
    printf("4. children est toujours terminé par NULL\n");
    printf("5. Libération mémoire récursive obligatoire\n");
}

/*
 * ========================================================================
 * CAS PARTICULIERS À MAÎTRISER POUR L'ÉVAL
 * ========================================================================
 */

void show_edge_cases_for_eval(void)
{
    printf("\nCAS PARTICULIERS IMPORTANTS\n");
    printf("===========================\n\n");
    
    printf("CAS 1: COMMANDE SIMPLE\n");
    printf("INPUT: \"ls -la\"\n");
    printf("→ Pas d'opérateur, parse_simple_command() direct\n");
    printf("→ Un seul NODE_CMD, pas de children sauf redirections\n\n");
    
    printf("CAS 2: PARENTHÈSES ENGLOBANTES\n");
    printf("INPUT: \"(ls | grep txt)\"\n");
    printf("→ matching_parentheses(0, n-1) = true\n");
    printf("→ Récursion avec parse(1, n-2) - supprime les parenthèses\n");
    printf("→ Résultat: NODE_PIPE (pas de NODE_SUBSHELL car englobantes)\n\n");
    
    printf("CAS 3: SOUS-SHELL AUTONOME\n");
    printf("INPUT: \"echo (ls | wc)\"\n");
    printf("→ Dans parse_simple_command, détecte PAREN_OPEN\n");
    printf("→ find_matching_parenthesis() pour trouver la fermeture\n");
    printf("→ create_subshell_node() avec le contenu\n\n");
    
    printf("CAS 4: PRÉCÉDENCE ÉGALE\n");
    printf("INPUT: \"cmd1 && cmd2 || cmd3\"\n");
    printf("→ && et || ont même précédence (1)\n");
    printf("→ Grâce à '<=', évaluation gauche-droite\n");
    printf("→ AST: NODE_OR_IF( NODE_AND_IF(cmd1,cmd2), cmd3 )\n\n");
    
    printf("CAS 5: REDIRECTIONS MULTIPLES\n");
    printf("INPUT: \"cat < in.txt > out.txt 2> err.txt\"\n");
    printf("→ NODE_CMD avec children[] = [REDIR_IN, REDIR_OUT, REDIR_ERR, NULL]\n");
    printf("→ extract_redirections() crée un tableau de nœuds redirect\n\n");
}

/*
 * ========================================================================
 * ERREURS COURANTES ET COMMENT LES ÉVITER
 * ========================================================================
 */

void show_common_mistakes_for_eval(void)
{
    printf("ERREURS COURANTES À L'ÉVAL\n");
    printf("==========================\n\n");
    
    printf("❌ ERREUR 1: Confusion précédence\n");
    printf("Question: \"Pourquoi | est sous && dans l'arbre ?\"\n");
    printf("✅ Réponse: \"Car && a précédence plus faible (1 vs 2).\"\n");
    printf("   L'opérateur faible devient racine, le fort devient enfant.\n\n");
    
    printf("❌ ERREUR 2: Oublier la terminaison NULL\n");
    printf("Code bugué: children = [left, right]  // Manque NULL !\n");
    printf("✅ Correct: children = [left, right, NULL]\n");
    printf("   Sinon segfault dans les boucles de parcours.\n\n");
    
    printf("❌ ERREUR 3: Confusion sur l'usage des champs\n");
    printf("Question: \"NODE_PIPE utilise quoi ?\"\n");
    printf("✅ Réponse: \"Seulement type et children. cmd et file ignorés.\"\n");
    printf("   Chaque type a son pattern d'utilisation spécifique.\n\n");
    
    printf("❌ ERREUR 4: Libération mémoire incorrecte\n");
    printf("Code bugué: free(node); free(node->children);  // Ordre inverse !\n");
    printf("✅ Correct: free(children); puis free(node);\n");
    printf("   Toujours libérer les dépendances avant le contenant.\n\n");
    
    printf("❌ ERREUR 5: Auto-référence root mal comprise\n");
    printf("Question: \"Pourquoi root->root = root ?\"\n");
    printf("✅ Réponse: \"Pour accéder au contexte global (envp, paths) \n");
    printf("   depuis n'importe quel nœud de l'arbre.\"\n\n");
}

/*
 * ========================================================================
 * QUESTIONS AVANCÉES POUR ÉVAL POUSSÉE
 * ========================================================================
 */

void advanced_eval_questions(void)
{
    printf("QUESTIONS AVANCÉES POSSIBLE À L'ÉVAL\n");
    printf("====================================\n\n");
    
    printf("Q: \"Comment optimiseriez-vous l'AST ?\"\n");
    printf("R: \"Pool de mémoire pour éviter malloc/free répétés.\n");
    printf("   Cache des nœuds fréquents. Compression des nœuds unaires.\"\n\n");
    
    printf("Q: \"Que se passe-t-il avec '(cmd1 | cmd2) && cmd3' ?\"\n");
    printf("R: \"Parenthèses forcent | à être évalué avant &&.\n");
    printf("   AST: NODE_AND_IF( NODE_SUBSHELL(...), cmd3 )\n");
    printf("   ou directement NODE_AND_IF( NODE_PIPE(...), cmd3 )\n");
    printf("   selon si les parenthèses sont significatives.\"\n\n");
    
    printf("Q: \"Comment gérez-vous les erreurs de parsing ?\"\n");
    printf("R: \"syntax_is_valid() avant construction AST.\n");
    printf("   Si échec malloc → cleanup partiel et return NULL.\n");
    printf("   Chaque fonction de création vérifie ses paramètres.\"\n\n");
    
    printf("Q: \"Différence avec un parseur LR/LALR ?\"\n");
    printf("R: \"Nous utilisons un parseur descendant récursif.\n");
    printf("   Plus simple à comprendre et implémenter.\n");
    printf("   Suffisant pour la grammaire shell simplifiée.\"\n\n");
    
    printf("Q: \"Comment étendre pour supporter ';' ?\"\n");
    printf("R: \"Ajouter NODE_SEQUENCE avec précédence très faible (0).\n");
    printf("   Modifier get_operator_precedence() et token_type_to_node_type().\n");
    printf("   L'architecture existante s'étend facilement.\"\n\n");
}

/*
 * ========================================================================
 * SCRIPT DE TEST POUR VALIDER VOTRE COMPRÉHENSION
 * ========================================================================
 */

void test_your_understanding(void)
{
    printf("TESTEZ VOTRE COMPRÉHENSION\n");
    printf("=========================\n\n");
    
    printf("Dessinez l'AST pour ces commandes:\n\n");
    
    printf("1. \"false || echo backup && echo success\"\n");
    printf("   Réponse attendue: NODE_AND_IF(\n");
    printf("                       NODE_OR_IF(false, echo backup),\n");
    printf("                       echo success\n");
    printf("                     )\n\n");
    
    printf("2. \"(echo start; ls) | tail -n 5\"\n");
    printf("   Note: Assume ';' implemented comme NODE_SEQUENCE\n");
    printf("   Réponse: NODE_PIPE(\n");
    printf("              NODE_SUBSHELL(NODE_SEQUENCE(echo start, ls)),\n");
    printf("              tail -n 5\n");
    printf("            )\n\n");
    
    printf("3. \"cat file1 file2 > out.txt 2> err.txt\"\n");
    printf("   Réponse: NODE_CMD {\n");
    printf("              args: [\"cat\", \"file1\", \"file2\", NULL],\n");
    printf("              children: [NODE_REDIR_OUT, NODE_REDIR_ERR, NULL]\n");
    printf("            }\n\n");
    
    printf("4. \"echo hello | { cat; cat; } | wc\"\n");
    printf("   Note: Assume '{}' comme sous-shell\n");
    printf("   Réponse: NODE_PIPE(\n");
    printf("              NODE_PIPE(\n");
    printf("                echo hello,\n");
    printf("                NODE_SUBSHELL(NODE_SEQUENCE(cat, cat))\n");
    printf("              ),\n");
    printf("              wc\n");
    printf("            )\n\n");
}

/*
 * ========================================================================
 * RÉSUMÉ FINAL POUR L'ÉVAL
 * ========================================================================
 */

void final_summary_for_eval(void)
{
    printf("RÉSUMÉ FINAL - À RETENIR ABSOLUMENT\n");
    printf("===================================\n\n");
    
    printf("📋 STRUCTURE t_ast:\n");
    printf("   - type: détermine l'interprétation\n");
    printf("   - children: tableau terminé par NULL\n");
    printf("   - cmd: pour NODE_CMD uniquement\n");
    printf("   - file: pour redirections uniquement\n");
    printf("   - root: accès contexte global\n\n");
    
    printf("🔄 ALGORITHME:\n");
    printf("   1. Trouver opérateur plus faible précédence\n");
    printf("   2. Si trouvé: diviser et récurser\n");
    printf("   3. Sinon: commande simple ou sous-shell\n");
    printf("   4. Créer nœud approprié\n\n");
    
    printf("⚖️ PRÉCÉDENCES:\n");
    printf("   - && et || : 1 (plus faible)\n");
    printf("   - | : 2 (moyen)\n");
    printf("   - autres : 3 (plus fort)\n");
    printf("   Faible → racine, Fort → feuilles\n\n");
    
    printf("🧠 TYPES DE NŒUDS:\n");
    printf("   - NODE_CMD: cmd.args + children(redirections)\n");
    printf("   - NODE_PIPE/AND_IF/OR_IF: children[0,1,NULL]\n");
    printf("   - NODE_SUBSHELL: children[0,NULL]\n");
    printf("   - NODE_REDIR_*: file\n\n");
    
    printf("🗑️ MÉMOIRE:\n");
    printf("   - Libération récursive\n");
    printf("   - children avant node\n");
    printf("   - Toujours vérifier NULL\n\n");
    
    printf("🎯 QUESTIONS CLÉS:\n");
    printf("   - \"Pourquoi récursif ?\" → Nature hiérarchique\n");
    printf("   - \"Précédence ?\" → Détermine forme arbre\n");
    printf("   - \"Différence types ?\" → Usage des champs\n");
    printf("   - \"Mémoire ?\" → Récursif, ordre important\n");
    
    printf("\n# 🌳 MAÎTRISE COMPLÈTE DE VOTRE AST POUR L'ÉVALUATION");
}

int main(void)
{
    demonstrate_ast_construction_for_eval();
    show_edge_cases_for_eval();
    show_common_mistakes_for_eval();
    advanced_eval_questions();
    test_your_understanding();
    final_summary_for_eval();
}