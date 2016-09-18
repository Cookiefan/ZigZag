const
	maxn=420000;
var
	c:array[0..maxn,0..1]of longint;
	t,next,fir,fa,col,sum,lc,rc,rest:array[0..maxn]of longint;
	v:array[0..maxn]of boolean;
	tot,i,n,m,x,y,z,rot,lca,ans:longint;
	sign,rb:char;
procedure update(x:longint);
begin
	if c[x,0]=0 then lc[x]:=col[x] else lc[x]:=lc[c[x,0]];
	if c[x,1]=0 then rc[x]:=col[x] else rc[x]:=rc[c[x,1]];
	sum[x]:=sum[c[x,0]]+sum[c[x,1]]+1;
	if col[x]=rc[c[x,0]] then sum[x]:=sum[x]-1;
	if col[x]=lc[c[x,1]] then sum[x]:=sum[x]-1;
end;

procedure fill(x,z:longint);
begin
        if x<>0 then
                begin
                        col[x]:=z;
                        rest[x]:=z;
                        lc[x]:=z;
                        rc[x]:=z;
                        sum[x]:=1;
                end;
end;



function root(x:longint):boolean;
begin
	exit((c[fa[x],0]<>x)and(c[fa[x],1]<>x));
end;

procedure clear(x:longint);
begin
	if rest[x]<>-1 then
		begin
                        fill(c[x,0],rest[x]);
                        fill(c[x,1],rest[x]);
			rest[x]:=-1;
		end;
end;

procedure relax(x:longint);
begin
        if not(root(x)) then relax(fa[x]);
        clear(x);
end;

procedure rotate(x:Longint);
var
	y,z,q,p:longint;
begin
	y:=fa[x]; z:=fa[y];
	if c[y,0]=x then p:=0 else p:=1;
	q:=p xor 1;
	if not root(y) then if c[z,0]=y then c[z,0]:=x else c[z,1]:=x;
	fa[x]:=z; fa[y]:=x; fa[c[x,q]]:=y;
	c[y,p]:=c[x,q]; c[x,q]:=y;
	update(y);
end;

procedure splay(x:Longint);
var
	y,z:longint;
begin
        relax(x);
	while not root(x) do
		begin
			y:=fa[x]; z:=fa[y];
			if not root(y) then
				if (c[y,0]=x)xor(c[z,0]=y) then rotate(x) else rotate(y);
			rotate(x);
		end;
	update(x);
end;

function access(x:longint):longint;
var
	y:longint;
begin
	y:=0;
	repeat
		splay(x);
		c[x,1]:=y;
		update(x);
		y:=x;x:=fa[x];
	until x=0;
	exit(y);
end;

procedure dfs(i:longint);
var
	j,k:longint;
begin
	v[i]:=true;
	j:=fir[i];
	while j>0 do
		begin
			k:=t[j];
			if not v[k] then
				begin
					fa[k]:=i;
					dfs(k);
				end;
			j:=next[j];
		end;
end;

procedure add(x,y:longint);
begin
	inc(tot);
	t[tot]:=y; next[tot]:=fir[x]; fir[x]:=tot;
end;

begin
        //assign(input,'paint.in'); reset(input);
        //assign(output,'paint.out'); rewrite(output);
	readln(n,m);
	for i:=1 to n do read(col[i]);
        readln;
	for i:=1 to n-1 do
		begin
			readln(x,y);
			add(x,y);
			add(y,x);
		end;
	rot:=random(n)+1;
	//rot:=1;
	fa[rot]:=0;
	dfs(rot);
	for i:=0 to n do rest[i]:=-1;
	for i:=1 to m do
		begin
			read(sign);read(rb);
			if sign='Q' then
				begin
					readln(x,y);
					access(x);
					lca:=access(y);
					splay(x);
					if x=lca then
						begin
							ans:=sum[c[lca,1]]+1;
							if lc[c[x,1]]=col[x] then ans:=ans-1;
						end
					else
						begin
							ans:=sum[c[lca,1]]+sum[x]+1;
							if lc[x]=col[lca] then ans:=ans-1;
							if lc[c[lca,1]]=col[lca] then ans:=ans-1
						end;
					writeln(ans);
				end
			else
				begin
					readln(x,y,z);
					access(x);
					lca:=access(y);
					splay(x);
					if lca=x then
						begin
                                                        fill(c[lca,1],z);
                                                        col[x]:=z;
						end
					else
						begin
                                                        fill(x,z);
                                                        fill(c[lca,1],z);
                                                        col[lca]:=z;
						end;
				end;
		end;
end.

