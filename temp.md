program             ->     statementList  
statementList       ->     statement    statementList'  
statementList'      ->     statement    statementList'   |  ϵ  
statement           ->     assignment   |  loop   |  if   |  io  
assignment          ->    const  type    id    assignment'   | type    id    assignment'   |  assign  
assignment'         ->     as_op    expression   ; | [  num   ]  assignment''    | ;
assignment''        ->     as_op    assignment'''   | ; 
assignment'''       ->    {  list   } ; |  string   ;
assign              ->     id    as_op   assign'  
assign'             ->     expression   ; | ;
list                ->     num   list'   |  boolean   list'   |  float   list'   |  charC   list'  
list'               ->    ,  list   |  ϵ  
loop                ->     for    scope   |  forEach    scope  
for                 ->    "for"  assignment   ;  expression   ;   assign  
forEach             ->    "foeach"  assignment   :  id   
scope               ->    {  statementList   }  
expression          ->     (  expression'  |  value | firstEspression
expression'         ->      type   )    expression | expression )
firstEspression     ->      value op expression | log_op    expression |ϵ
op                  ->     rel_op | ar_op  |  log_op
io                  ->     in   |  out  
out                 ->    ->  expression   ;
in                  ->     <-  id   ;
value               ->    charC   |  num   |  float   |  id   |  boolean            
boolean             ->    true | false
if                  ->    "if"  if'   if''  
if'                 ->    expression  scope  
if''                ->     else   if''   |  ϵ  
else                ->    "else"  else'   
else'               ->    { statementList } | "if" if' if''