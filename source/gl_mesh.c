/*
Copyright (C) 2003-2006 Andrey Nazarov

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "gl_local.h"

#define RF_SHELL_MASK	( RF_SHELL_RED | RF_SHELL_GREEN | RF_SHELL_BLUE | RF_SHELL_DOUBLE | RF_SHELL_HALF_DAM )

static vec3_t oldscale;
static vec3_t newscale;
static vec3_t translate;

typedef void (*meshTessFunc_t)( aliasMesh_t *, int, int );

static void Tess_Mesh( aliasMesh_t *mesh, int oldframe, int newframe ) {
	aliasVert_t *src_vert;
	vec_t *dst_vert;
    int i, count;
	vec_t *normal;

	src_vert = &mesh->verts[newframe * mesh->numVerts];
    dst_vert = tess.vertices;
    count = mesh->numVerts;
	if( glr.ent->flags & RF_SHELL_MASK ) {
		for( i = 0; i < count; i++ ) {
			normal = bytedirs[src_vert->normalIndex];

			dst_vert[0] = normal[0] * POWERSUIT_SCALE +
                src_vert->pos[0] * newscale[0] + translate[0];
			dst_vert[1] = normal[1] * POWERSUIT_SCALE +
                src_vert->pos[1] * newscale[1] + translate[1];
			dst_vert[2] = normal[2] * POWERSUIT_SCALE +
                src_vert->pos[2] * newscale[2] + translate[2];
	        
			src_vert++;
			dst_vert += 4;
		}
	} else {
		for( i = 0; i < count; i++ ) {
			dst_vert[0] = src_vert->pos[0] * newscale[0] + translate[0];
			dst_vert[1] = src_vert->pos[1] * newscale[1] + translate[1];
			dst_vert[2] = src_vert->pos[2] * newscale[2] + translate[2];
	        
			src_vert++;
			dst_vert += 4;
		}
	}

	c.trisDrawn += count;
}

static void Tess_LerpedMesh( aliasMesh_t *mesh, int oldframe, int newframe ) {
	aliasVert_t *src_oldvert;
	aliasVert_t *src_newvert;
	vec_t *dst_vert;
    int i, count;
	vec_t *normal;

	src_oldvert = &mesh->verts[oldframe * mesh->numVerts];
	src_newvert = &mesh->verts[newframe * mesh->numVerts];
    dst_vert = tess.vertices;
    count = mesh->numVerts;
	if( glr.ent->flags & RF_SHELL_MASK ) {
		for( i = 0; i < count; i++ ) {
			normal = bytedirs[src_newvert->normalIndex];

			dst_vert[0] = normal[0] * POWERSUIT_SCALE +
				src_oldvert->pos[0] * oldscale[0] +
				src_newvert->pos[0] * newscale[0] + translate[0];
			dst_vert[1] = normal[1] * POWERSUIT_SCALE +
				src_oldvert->pos[1] * oldscale[1] +
				src_newvert->pos[1] * newscale[1] + translate[1];
			dst_vert[2] = normal[2] * POWERSUIT_SCALE +
				src_oldvert->pos[2] * oldscale[2] +
				src_newvert->pos[2] * newscale[2] + translate[2];
	        
			src_oldvert++;
			src_newvert++;
			dst_vert += 4;
		}
	} else {
		for( i = 0; i < count; i++ ) {
			dst_vert[0] =
				src_oldvert->pos[0] * oldscale[0] +
				src_newvert->pos[0] * newscale[0] + translate[0];
			dst_vert[1] =
				src_oldvert->pos[1] * oldscale[1] +
				src_newvert->pos[1] * newscale[1] + translate[1];
			dst_vert[2] =
				src_oldvert->pos[2] * oldscale[2] +
				src_newvert->pos[2] * newscale[2] + translate[2];
	        
			src_oldvert++;
			src_newvert++;
			dst_vert += 4;
		}
	}
	
	c.trisDrawn += count;

}

void GL_SetAliasColor( vec3_t origin, vec3_t color ) {
	entity_t *ent = glr.ent;
	float f, m;
	int i;

	if( ent->flags & RF_SHELL_MASK ) {
		VectorClear( color );
		if( ent->flags & RF_SHELL_HALF_DAM ) {
			color[0] = 0.56f;
			color[1] = 0.59f;
			color[2] = 0.45f;
		}
		if( ent->flags & RF_SHELL_DOUBLE ) {
			color[0] = 0.9f;
			color[1] = 0.7f;
		}
		if( ent->flags & RF_SHELL_RED ) {
			color[0] = 1;
		}
		if( ent->flags & RF_SHELL_GREEN ) {
			color[1] = 1;
		}
		if( ent->flags & RF_SHELL_BLUE ) {
			color[2] = 1;
		}
	} else if( ent->flags & RF_FULLBRIGHT ) {
		VectorSet( color, 1, 1, 1 );
	} else {
		GL_LightPoint( origin, color );

		if( ent->flags & RF_MINLIGHT ) {
			for( i = 0; i < 3; i++ ) {
				if( color[i] > 0.1f ) {
					break;
				}
			}
			if( i == 3 ) {
				VectorSet( color, 0.1f, 0.1f, 0.1f );
			}
		}

		if( ent->flags & RF_GLOW ) {
			f = 0.1f * sin( glr.fd.time * 7 );
			for( i = 0; i < 3; i++ ) {
				m = color[i] * 0.8f;
				color[i] += f;
				if( color[i] < m ) {
					color[i] = m;
				}
			}
		}
	}

	if( glr.fd.rdflags & RDF_IRGOGGLES && ent->flags & RF_IR_VISIBLE ) {
		VectorSet( color, 1, 0, 0 );
	}
}


void GL_DrawAliasModel( model_t *model ) {
	entity_t *ent = glr.ent;
	image_t *image;
	int oldframeIdx, newframeIdx;
	aliasFrame_t *newframe, *oldframe;
	aliasMesh_t *mesh, *last;
	meshTessFunc_t tessFunc;
	float frontlerp, backlerp;
	vec3_t origin;
	vec3_t bounds[2];
	vec_t radius;
	glStateBits_t bits;
	glCullResult_t cull;
	vec3_t color;
	float alpha;

	newframeIdx = ent->frame;
	if( newframeIdx < 0 || newframeIdx >= model->numFrames ) {
		Com_DPrintf( "GL_DrawAliasModel: no such frame %d\n", newframeIdx );
		newframeIdx = 0;
	}

	oldframeIdx = ent->oldframe;
	if( oldframeIdx < 0 || oldframeIdx >= model->numFrames ) {
		Com_DPrintf( "GL_DrawAliasModel: no such oldframe %d\n", oldframeIdx );
		oldframeIdx = 0;
	}

	newframe = model->frames + newframeIdx;

	backlerp = ent->backlerp;
	frontlerp = 1.0f - backlerp;

	/* interpolate origin, if necessarry */
	if( ent->flags & RF_FRAMELERP ) {
        LerpVector( ent->oldorigin, ent->origin, frontlerp, origin );
	} else {
		VectorCopy( ent->origin, origin );
	}

	if( newframeIdx == oldframeIdx || backlerp == 0 ) {
		oldframe = NULL;

		if( glr.entrotated ) {
			cull = GL_CullSphere( origin, newframe->radius );
			if( cull == CULL_OUT ) {
				c.spheresCulled++;
				return;
			}
			if( cull == CULL_CLIP ) {
				cull = GL_CullLocalBox( origin, newframe->bounds );
				if( cull == CULL_OUT ) {
					c.rotatedBoxesCulled++;
					return;
				}
			}
		} else {
			VectorAdd( newframe->bounds[0], origin, bounds[0] );
			VectorAdd( newframe->bounds[1], origin, bounds[1] );
			if( GL_CullBox( bounds ) == CULL_OUT ) {
				c.boxesCulled++;
				return;
			}
		}

		VectorCopy( newframe->scale, newscale );
		VectorCopy( newframe->translate, translate );
		tessFunc = Tess_Mesh;
	} else {
		oldframe = model->frames + oldframeIdx;

		if( glr.entrotated ) {
			radius = newframe->radius > oldframe->radius ?
                newframe->radius : oldframe->radius;
			cull = GL_CullSphere( origin, radius );
			if( cull == CULL_OUT ) {
				c.spheresCulled++;
				return;
			}
			UnionBounds( newframe->bounds, oldframe->bounds, bounds );
			if( cull == CULL_CLIP ) {
				cull = GL_CullLocalBox( origin, bounds );
				if( cull == CULL_OUT ) {
					c.rotatedBoxesCulled++;
					return;
				}
			}
		} else {
			UnionBounds( newframe->bounds, oldframe->bounds, bounds );
			VectorAdd( bounds[0], origin, bounds[0] );
			VectorAdd( bounds[1], origin, bounds[1] );
			if( GL_CullBox( bounds ) == CULL_OUT ) {
				c.boxesCulled++;
				return;
			}
		}

		VectorScale( oldframe->scale, backlerp, oldscale );
		VectorScale( newframe->scale, frontlerp, newscale );

        LerpVector( oldframe->translate, newframe->translate,
            frontlerp, translate );

		tessFunc = Tess_LerpedMesh;
	}

	/* setup color */
	GL_SetAliasColor( origin, color );

	/* setup transparency */
	bits = GLS_DEFAULT;
	alpha = 1;
	if( ent->flags & RF_TRANSLUCENT ) {
		alpha = ent->alpha;
		bits |= GLS_BLEND_BLEND|GLS_DEPTHMASK_FALSE;
	}

	GL_TexEnv( GL_MODULATE );
    
	qglPushMatrix();

	qglTranslatef( origin[0], origin[1], origin[2] );
	
	qglRotatef( ent->angles[YAW],   0, 0, 1 );
	qglRotatef( ent->angles[PITCH], 0, 1, 0 );
	qglRotatef( ent->angles[ROLL],  1, 0, 0 );

	if( ent->flags & RF_DEPTHHACK ) {
		qglDepthRange( 0, 0.25f );
	}
	if( ( ent->flags & (RF_WEAPONMODEL|RF_LEFTHAND) ) ==
            (RF_WEAPONMODEL|RF_LEFTHAND) )
    {
		qglMatrixMode( GL_PROJECTION );
		qglScalef( -1, 1, 1 );
		qglMatrixMode( GL_MODELVIEW );
		qglCullFace( GL_BACK );
	}
    
	qglColor4f( color[0], color[1], color[2], alpha );
	qglVertexPointer( 3, GL_FLOAT, 16, tess.vertices );

	last = model->meshes + model->numMeshes;
	for( mesh = model->meshes; mesh != last; mesh++ ) {
		if( ent->flags & RF_SHELL_MASK ) {
			image = r_whiteimage;
		} else {
			if( ent->skin ) {
				image = R_ImageForHandle( ent->skin );
			} else {
				if( ( unsigned )ent->skinnum >= MAX_MD2SKINS ) {
					Com_DPrintf( "GL_DrawAliasModel: no such skin: %d\n",
						ent->skinnum );
					image = mesh->skins[0];
				} else {
					image = mesh->skins[ent->skinnum];
					if( !image ) {
						image = mesh->skins[0];
					}
				}
			}
			if( !image ) {
				image = r_notexture;
			}
		}

        if( !( image->flags & if_paletted ) && ( image->flags & if_transparent ) ) {
    	    GL_Bits( bits | GLS_BLEND_BLEND );
        } else {
    	    GL_Bits( bits );
        }
		GL_BindTexture( image->texnum );

		tessFunc( mesh, oldframeIdx, newframeIdx );

		qglTexCoordPointer( 2, GL_FLOAT, 0, mesh->tcoords );
		if( qglLockArraysEXT ) {
			qglLockArraysEXT( 0, mesh->numVerts );
		}
		qglDrawElements( GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT,
				mesh->indices );
		if( gl_showtris->integer ) {
			Tess_DrawSurfaceTriangles( ( int * )mesh->indices,
                    mesh->numIndices );
		}
		if( qglUnlockArraysEXT ) {
			qglUnlockArraysEXT();
		}
	}

	if( ent->flags & RF_DEPTHHACK ) {
		qglDepthRange( 0, 1 );
	}

	if( ( ent->flags & (RF_WEAPONMODEL|RF_LEFTHAND) ) ==
            (RF_WEAPONMODEL|RF_LEFTHAND) )
    {
		qglMatrixMode( GL_PROJECTION );
		qglScalef( -1, 1, 1 );
		qglMatrixMode( GL_MODELVIEW );
		qglCullFace( GL_FRONT );
	}
	
	qglPopMatrix();

}

