/* Exercise 6.7 */

/*
	Higher level number (L1, L2, ...) = tighter bind (ret = returned)
	
	Expression:
		Level1
		Expression '|' Level1
	Level1:
		Level2
		Level1 '^' Level2
	Level2:
		Level3
		Level2 '&' Level3
	Level3:
		Level4
		'!' Level3
		'~' Level3
		'(' Expression ')'
	Level4:
		Operand
*/

/*
	Example 3: ~(op1 | op2 | op3 & op4 ^ ~op5) ^ !op6
		Expression->case:L1
			L1->case:L2
				L2->case:L3
					L3->case:'~'
						L3->case:'('
							Expression->case:L1
								L1->case:L2
									L2->case:L3
										L3->case:L4
											L4->case:Operand
												Operand ret op1
											L4 ret Operand
										L3 ret L4
									L2 ret L3
								L1 ret L2
							Expression->case:Expression '|' L1
								L1->case:L2
									L2->case:L3
										L3->case:L4
											L4->case:Operand
												Operand ret op2
											L4 ret Operand
										L3 ret L4
									L2 ret L3
								L1 ret L2
							Expression->case:Expression '|' L1
								L1->case:L2
									L2->case:L3
										L3->case:L4
											L4->case:Operand
												Operand ret op3
											L4 ret Operand
										L3 ret L4
									L2->case:L2 '&' L3
										L3->case:L4
											L4->case:Operand
												Operand ret op4
											L4 ret Operand
										L3 ret L4
									L2 ret L2 '&' L3
								L1->case:L1 '^' L2
									L2->case:L3
										L3->case:'~' L3
											L3->case:L4
												L4->case:Operand
													Operand ret op3
												L4 ret Operand
											L3 ret L4
										L3 ret '~' L3
									L2 ret L3
								L1 ret L1 '^' L2
							Expression ret Expression '|' L1
						L3 ret '(' Expression ')'
					L3 ret '~' L3
				L2 ret L3
			L1->case:L1 '^' L2
				L2->case:L3
					L3->case:'!' L3
						L3->case:L4
							L4->case:Operand
								Operand ret op3
							L4 ret Operand
						L3 ret L4
					L3 ret '!' L3
				L2 ret L3
			L1 ret L1 '^' L2
		Expression ret L1
*/
